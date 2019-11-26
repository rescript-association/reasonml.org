open Util.ReactStuff;
module Link = Next.Link;

let link = "no-underline block text-inherit hover:cursor-pointer hover:text-white text-white-80 mb-px";
let activeLink = "text-inherit font-normal text-fire-80 border-b border-fire-80";

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

    <div className="sm:font-normal relative" onMouseEnter>
      <div className="flex items-center">
        <a
          onMouseDown
          className={
            (active ? activeLink : link)
            ++ " flex items-center hover:cursor-pointer "
            ++ (isOpen ? " text-white" : "")
          }>
          title->s
          <span
            className="fill-current flex-no-wrap inline-block ml-2 w-3 h-2">
            <Caret direction />
          </span>
        </a>
      </div>
      <div
        className={
          (isOpen ? "block" : "hidden")
          ++ " sm:fixed sm:left-0 sm:border-night sm:mt-4 sm:border-t bg-night-dark w-full h-16"
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

[@react.component]
let make = (~isOpen=false, ~toggle=() => (), ~route="/") => {
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

  <nav
    ref={ReactDOMRe.Ref.domRef(outerRef)}
    id="header"
    style={Style.make(~minWidth, ())}
    className="fixed flex justify-center z-10 top-0 w-full h-16 bg-night-dark shadow text-white-80 text-xl sm:text-base">
    <div
      className="flex justify-between pl-4 items-center h-full w-full sm:max-w-xl">
      <div className="lg:mb-3 w-8 lg:w-20">
        <Link href="/">
          <a>
            <picture>
              <source
                srcSet="/static/reason_logo_full.svg"
                media="(min-width: 993px)"
              />
              <img
                className="h-8 w-auto inline-block"
                src="/static/reason_logo.svg"
              />
            </picture>
          </a>
        </Link>
      </div>
      /* Burger Button */
      <button
        className="h-full px-4 sm:hidden flex items-center hover:text-white"
        onClick={evt => {
          ReactEvent.Mouse.preventDefault(evt);
          toggle();
        }}>
        <img className="w-full block" src="/static/ic_drawer_dots.svg" />
      </button>
      <div
        style={Style.make(~minWidth, ())}
        className={
          (isOpen ? "flex" : "hidden")
          ++ " flex-col fixed top-0 left-0 h-full sm:w-9/12 bg-night-dark sm:h-auto sm:flex sm:relative sm:flex-row sm:justify-between"
        }>
        <div className="flex h-16 justify-between items-center sm:hidden">
          <Link href="/">
            <a className="w-24"> <img src="/static/reason_logo.svg" /> </a>
          </Link>
          <span
            onClick={evt => {
              ReactEvent.Mouse.preventDefault(evt);
              toggle();
            }}
            className="inline-block text-center w-6 text-2xl font-bold">
            "X"->s
          </span>
        </div>
        <div
          className="flex flex-col sm:flex-row sm:justify-between sm:w-full max-w-sm">
          {Belt.Array.mapWithIndex(
             collapsibles,
             (idx, c) => {
               let {href, title, children, state} = c;
               let onStateChange = (~id, state) =>
                 {setCollapsibles(prev =>
                    Belt.Array.map(prev, c =>
                      if (c.title === id) {
                        {...c, state};
                      } else {
                        {...c, state: Closed};
                      }
                    )
                  )};
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
           ->ate}
          <Link href="/try">
            <a className={linkOrActiveLink(~target="/try", ~route)}>
              "Playground"->s
            </a>
          </Link>
          <Link href="/blog">
            <a className={linkOrActiveLink(~target="/blog", ~route)}>
              "Blog"->s
            </a>
          </Link>
          <Link href="/community">
            <a className={linkOrActiveLink(~target="/community", ~route)}>
              "Community"->s
            </a>
          </Link>
        </div>
        <div className="hidden lg:flex lg:justify-between lg:w-2/12">
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
        className="hidden sm:flex sm:w-16 sm:justify-center sm:border-l sm:border-r sm:border-night sm:h-full">
        <img src="/static/ic_search_small.svg" className="w-6 h-6" />
      </button>
    </div>
  </nav>;
};
