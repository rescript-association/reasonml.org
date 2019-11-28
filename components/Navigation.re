open Util.ReactStuff;
module Link = Next.Link;

let link = "no-underline block text-inherit hover:cursor-pointer hover:text-white text-white-80 mb-px";
let activeLink = "text-inherit font-normal text-fire border-b border-fire";

let linkOrActiveLink = (~target, ~route) => {
  target === route ? activeLink : link;
};

module CollapsibleLink = {
  // KeepOpen = Menu has been opened and should stay open
  type state =
    | KeepOpen
    | HoverOpen
    | Closed;

  [@react.component]
  let make =
      (
        ~title: string,
        ~onStateChange: (~id: string, state) => unit,
        ~allowHover=true,
        ~allowInteraction=true,
        ~id: string,
        ~state: state,
        ~active=false,
        ~children,
      ) => {
    // This is not onClick, because we want to prevent
    // text selection on multiple clicks
    let onMouseDown = evt => {
      ReactEvent.Mouse.preventDefault(evt);
      ReactEvent.Mouse.stopPropagation(evt);

      onStateChange(
        ~id,
        switch (state) {
        | Closed => KeepOpen
        | HoverOpen => Closed
        | KeepOpen => Closed
        },
      );
    };

    let onMouseEnter = evt => {
      ReactEvent.Mouse.preventDefault(evt);
      if (allowHover) {
        onStateChange(~id, HoverOpen);
      };
    };

    let isOpen =
      switch (state) {
      | Closed => false
      | KeepOpen
      | HoverOpen => true
      };

    let direction = isOpen ? `Up : `Down;

    <div className="relative" onMouseEnter>
      <div className="flex items-center">
        <a
          onMouseDown
          className={
            (active ? activeLink : link)
            ++ " flex items-center hover:cursor-pointer "
            ++ (isOpen ? " text-white" : "")
          }>
          title->s
          <span className="fill-current flex-no-wrap inline-block ml-2 w-2">
            <Icon.Caret
              direction
              className={active ? "text-inherit" : "text-night-light"}
            />
          </span>
        </a>
      </div>
      <div
        className={
          (isOpen ? "block" : "hidden")
          ++ " fixed left-0 mt-4 border-night border-t bg-night-dark w-full h-full sm:h-16"
        }>
        children
      </div>
    </div>;
  };
};

let useOutsideClick: (ReactDOMRe.Ref.t, unit => unit) => unit = [%raw
  (outerRef, trigger) => {j|{
      function handleClickOutside(event) {
        if (outerRef.current && !outerRef.current.contains(event.target)) {
          trigger();
        }
      }

      React.useEffect(() => {
        document.addEventListener("mousedown", handleClickOutside);
        return () => {
          document.removeEventListener("mousedown", handleClickOutside);
        };
      });

    }|j}
];

let useWindowWidth: unit => option(int) = [%raw
  () => {j|{
  const isClient = typeof window === 'object';

  function getSize() {
    return {
      width: isClient ? window.innerWidth : undefined,
      height: isClient ? window.innerHeight : undefined
    };
  }

  const [windowSize, setWindowSize] = React.useState(getSize);

  React.useEffect(() => {
    if (!isClient) {
      return false;
    }

    function handleResize() {
      setWindowSize(getSize());
    }

    window.addEventListener('resize', handleResize);
    return () => window.removeEventListener('resize', handleResize);
  }, []); // Empty array ensures that effect is only run on mount and unmount

  if(windowSize) {
    return windowSize.width;
  }
  return null;
  }|j}
];

type collapsible = {
  title: string,
  children: React.element,
  href: string,
  state: CollapsibleLink.state,
};

module SubNav = {
  module DocsLinkSection = {
    [@react.component]
    let make = () => {
      <div> "Docs Items"->s </div>;
    };
  };

  module ApisLinkSection = {
    [@react.component]
    let make = () => {
      let jsTheme = ColorTheme.toCN(`Js);
      let reTheme = ColorTheme.toCN(`Reason);

      let jsItems = [|
        ("Belt Stdlib", "/apis/javascript/latest/belt"),
        ("Js Module", "/apis/javascript/latest/js"),
      |];

      <div className="">
        <div className=reTheme>
          <Link href="/apis">
            <a className="uppercase text-sm text-primary"> "Overview"->s </a>
          </Link>
        </div>
        <div className=jsTheme>
          <Link href="/apis/javascript/latest">
            <a
              className="uppercase tracking-wide text-sm text-primary font-black">
              "JavaScript"->s
            </a>
          </Link>
        </div>
      </div>;
    };
  };
};

/* isOpen: if the mobile overlay is toggled open */
[@react.component]
let make = (~isOverlayOpen=false, ~toggle=() => (), ~route="/") => {
  let minWidth = "20rem";

  let (collapsibles, setCollapsibles) =
    React.useState(_ =>
      [|
        {
          title: "Docs",
          href: "/docs",
          children: <SubNav.DocsLinkSection />,
          state: Closed,
        },
        {
          title: "API",
          href: "/apis",
          children: <SubNav.ApisLinkSection />,
          state: Closed // TODO: Set back to Closed
        },
      |]
    );

  let resetCollapsibles = () =>
    setCollapsibles(prev => Belt.Array.map(prev, c => {...c, state: Closed}));

  let outerRef = React.useRef(Js.Nullable.null);
  useOutsideClick(ReactDOMRe.Ref.domRef(outerRef), resetCollapsibles);

  let windowWidth = useWindowWidth();

  // Don't allow hover behavior for collapsibles if mobile navigation is on
  let allowHover =
    switch (windowWidth) {
    | Some(width) => width > 576 // Value noted in tailwind config
    | None => true
    };

  let collapsibleItems =
    Belt.Array.mapWithIndex(
      collapsibles,
      (idx, c) => {
        let {href, title, children, state} = c;
        let onStateChange = (~id, state) => {
          setCollapsibles(prev => {
            /* This is important to close the nav overlay, before showing the subnavigation */
            if (isOverlayOpen) {
              toggle();
            };
            Belt.Array.map(prev, c =>
              if (c.title === id) {
                {...c, state};
              } else {
                {...c, state: Closed};
              }
            );
          });
        };
        <CollapsibleLink
          id=title
          onStateChange
          key={idx->Belt.Int.toString}
          allowHover
          title
          active={Js.String2.startsWith(route, href)}
          state>
          children
        </CollapsibleLink>;
      },
    )
    ->ate;

  <nav
    ref={ReactDOMRe.Ref.domRef(outerRef)}
    id="header"
    style={Style.make(~minWidth, ())}
    className="fixed flex justify-center z-10 top-0 w-full h-16 bg-night-dark shadow text-white-80 text-base">
    <div
      className="flex justify-between pl-4 items-center h-full w-full max-w-xl">
      <div className="lg:mb-3 h-8 w-8 lg:w-20">
        <a href="/">
          <picture>
            <source
              srcSet="/static/reason_logo_full.svg"
              media="(min-width: 992px)"
            />
            <img
              className="h-8 w-auto inline-block"
              src="/static/reason_logo.svg"
            />
          </picture>
        </a>
      </div>
      /* Desktop horizontal navigation */
      <div
        className="flex justify-center sm:justify-between bg-night-dark w-10/12 sm:w-9/12 sm:h-auto sm:relative">
        <div
          className="flex justify-between w-2/4 sm:w-full max-w-sm"
          style={Style.make(~minWidth="13rem", ())}>
          <button
            className="sm:hidden flex px-4 items-center justify-center h-full">
            <Icon.MagnifierGlass className="w-5 h-5 hover:text-white" />
          </button>
          collapsibleItems
          <Link href="/try">
            <a
              className={
                "hidden sm:block " ++ linkOrActiveLink(~target="/try", ~route)
              }>
              "Playground"->s
            </a>
          </Link>
          <Link href="/blog">
            <a
              className={
                "hidden sm:block "
                ++ linkOrActiveLink(~target="/blog", ~route)
              }>
              "Blog"->s
            </a>
          </Link>
          <Link href="/community">
            <a
              className={
                "hidden sm:block "
                ++ linkOrActiveLink(~target="/community", ~route)
              }>
              "Community"->s
            </a>
          </Link>
        </div>
        <div className="hidden lg:-mr-6 lg:flex lg:justify-between lg:w-20 ">
          <a
            href="https://github.com/reason-association/reasonml.org"
            rel="noopener noreferrer"
            target="_blank"
            className=link>
            <Icon.Github className="w-5 h-5" />
          </a>
          <a
            href="https://twitter.com/reasonml"
            rel="noopener noreferrer"
            target="_blank"
            className=link>
            <Icon.Twitter className="w-5 h-5" />
          </a>
          <a
            href="https://discord.gg/reasonml"
            rel="noopener noreferrer"
            target="_blank"
            className=link>
            <Icon.Discord className="w-5 h-5" />
          </a>
        </div>
      </div>
      <button
        className="hidden sm:flex sm:px-4 sm:items-center sm:justify-center sm:border-l sm:border-r sm:border-night sm:h-full">
        <Icon.MagnifierGlass className="w-5 h-5 hover:text-white" />
      </button>
    </div>
    /* Burger Button */
    <button
      className="h-full px-4 sm:hidden flex items-center hover:text-white"
      onClick={evt => {
        ReactEvent.Mouse.preventDefault(evt);
        resetCollapsibles();
        toggle();
      }}>
      <Icon.DrawerDots
        className={"h-1 w-auto block " ++ (isOverlayOpen ? "text-fire" : "")}
      />
    </button>
    /* Mobile overlay */
    <div
      style={Style.make(~minWidth, ~top="4rem", ())}
      className={
        (isOverlayOpen ? "flex" : "hidden")
        ++ " sm:hidden flex-col fixed top-0 left-0 h-full w-full sm:w-9/12 bg-night-dark sm:h-auto sm:flex sm:relative sm:flex-row sm:justify-between"
      }>
      <div className="border-night border-t"> "mobile"->s </div>
    </div>
  </nav>;
};
