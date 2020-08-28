open Util.ReactStuff;
module Link = Next.Link;

let link = "no-underline block text-inherit hover:cursor-pointer hover:text-white text-white-80 mb-px";
let activeLink = "text-inherit font-normal text-fire border-b border-fire";

let linkOrActiveLink = (~target, ~route) => {
  target === route ? activeLink : link;
};

let linkOrActiveLinkSubroute = (~target, ~route) => {
  Js.String2.startsWith(route, target) ? activeLink : link;
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

    // This onClick is required for iOS12 safari.
    // There seems to be a bug where mouse events
    // won't be registered, unless an onClick event
    // is attached
    // DO NOT REMOVE, OTHERWISE THE COLLAPSIBLE WON'T WORK
    let onClick = _ => ();

    let direction = isOpen ? `Up : `Down;

    <div className="relative" onMouseEnter>
      <div className="flex items-center">
        <a
          onMouseDown
          onClick
          className={
            (active ? activeLink : link)
            ++ " border-none flex items-center hover:cursor-pointer "
            ++ (isOpen ? " text-white" : "")
          }>
          <span className={active ? "border-b border-fire" : ""}>
            title->s
          </span>
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
          (isOpen ? "flex" : "hidden")
          ++ " fixed left-0 border-night border-t bg-night-dark min-w-320 w-full h-full sm:h-auto sm:justify-center"
        }
        style={Style.make(~marginTop="1.375rem", ())}>
        <div className="max-w-xl w-full"> children </div>
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
  children: string => React.element,
  href: string,
  state: CollapsibleLink.state,
};

module SubNav = {
  module DocsLinks = {
    [@react.component]
    let make = (~route: string) => {
      let jsTheme = ColorTheme.toCN(`Js);
      let reTheme = ColorTheme.toCN(`Reason);

      let languageItems = [|
        ("Introduction", "/docs/manual/latest/introduction"),
        ("Cheatsheet", "/docs/manual/latest/syntax-cheatsheet"),
      |];

      let recompItems = [|
        ("BuckleScript", "/docs/reason-compiler/latest/introduction"),
        ("ReasonReact", "/docs/reason-react/latest/introduction"),
        ("GenType", "/docs/gentype/latest/introduction"),
      |];

      let activeThemeLink = "font-normal text-primary border-b border-primary";

      let sectionClass = "pb-12 mt-12 border-b border-night last:border-b-0 lg:w-1/3";
      let overlineClass = "font-black uppercase text-sm tracking-wide text-primary-80";

      let sectionUl = "flex flex-wrap mt-8 list-primary list-inside lg:w-auto max-w-md";

      <div className="lg:flex lg:flex-row px-4 max-w-xl">
        <div className={reTheme ++ " " ++ sectionClass}>
          <Link href="/docs/manual/latest/introduction">
            <a className=overlineClass> "Language Manual"->s </a>
          </Link>
          <ul className=sectionUl>
            {languageItems
             ->Belt.Array.mapWithIndex((idx, (title, href)) => {
                 let active =
                   route == href
                     ? activeThemeLink ++ " hover:text-primary cursor-auto"
                     : "";
                 <li
                   className="w-1/2 xs:w-1/2 h-10"
                   key={Belt.Int.toString(idx)}>
                   <Link href>
                     <a
                       className={
                         "text-white-80 hover:text-white hover:cursor-pointer "
                         ++ active
                       }>
                       title->s
                     </a>
                   </Link>
                 </li>;
               })
             ->ate}
          </ul>
        </div>
        <div className={jsTheme ++ " " ++ sectionClass}>
          <Link href="/docs/reason-compiler/latest/introduction">
            <a className=overlineClass> "JavaScript"->s </a>
          </Link>
          <ul className=sectionUl>
            {recompItems
             ->Belt.Array.mapWithIndex((idx, (title, href)) => {
                 let active =
                   route == href
                     ? activeThemeLink ++ " hover:text-primary cursor-auto"
                     : "";
                 <li
                   className="w-1/2 xs:w-1/2 h-10"
                   key={Belt.Int.toString(idx)}>
                   <Link href>
                     <a
                       className={
                         "text-white-80 hover:text-white hover:cursor-pointer "
                         ++ active
                       }>
                       title->s
                     </a>
                   </Link>
                 </li>;
               })
             ->ate}
          </ul>
        </div>
      </div>;
    };
  };

  module ApiLinks = {
    [@react.component]
    let make = (~route: string) => {
      let jsTheme = ColorTheme.toCN(`Js);
      let reTheme = ColorTheme.toCN(`Reason);

      let jsItems = [|
        ("Belt Stdlib", "/apis/javascript/latest/belt"),
        ("Js Module", "/apis/javascript/latest/js"),
        /*("Module 3", "/apis/javascript/latest/mod3"),*/
        /*("Module 4", "/apis/javascript/latest/mod4"),*/
      |];

      let sectionClass = "pb-12 mt-12 border-b border-night last:border-b-0 lg:w-1/4";
      let overlineClass = "font-black uppercase text-sm tracking-wide text-primary-80";

      let sectionUl = "flex flex-wrap mt-8 list-primary list-inside lg:w-auto max-w-md";

      <div className="lg:flex lg:flex-row px-4 max-w-xl">
        <div className={reTheme ++ " " ++ sectionClass}>
          <Link href="/apis">
            <a className=overlineClass> "Overview"->s </a>
          </Link>
        </div>
        <div className={jsTheme ++ " " ++ sectionClass}>
          <Link href="/apis/javascript/latest">
            <a className=overlineClass> "JavaScript"->s </a>
          </Link>
          <ul className=sectionUl>
            {jsItems
             ->Belt.Array.mapWithIndex((idx, (title, href)) => {
                 let active =
                   Js.String2.startsWith(route, href) ? "text-primary" : "";
                 <li
                   className="w-1/2 xs:w-1/2 h-10"
                   key={Belt.Int.toString(idx)}>
                   <Link href>
                     <a
                       className={
                         "text-white-80 hover:text-white hover:cursor-pointer "
                         ++ active
                       }>
                       title->s
                     </a>
                   </Link>
                 </li>;
               })
             ->ate}
          </ul>
        </div>
      </div>;
    };
  };
};

module MobileNav = {
  [@react.component]
  let make = (~route: string) => {
    let base = "font-light mx-4 py-5 text-white-80 border-b border-night";
    let extLink = "block hover:cursor-pointer hover:text-white text-night-light";
    <div className="border-night border-t">
      <ul>
        <li className=base>
          <Link href="/try">
            <a className={linkOrActiveLink(~target="/try", ~route)}>
              "Playground"->s
            </a>
          </Link>
        </li>
        <li className=base>
          <Link href="/blog">
            <a className={linkOrActiveLinkSubroute(~target="/blog", ~route)}>
              "Blog"->s
            </a>
          </Link>
        </li>
        <li className=base>
          <Link href="/community">
            <a className={linkOrActiveLink(~target="/community", ~route)}>
              "Community"->s
            </a>
          </Link>
        </li>
        <li className=base>
          <a
            href="https://twitter.com/reasonml"
            rel="noopener noreferrer"
            target="_blank"
            className=extLink>
            "Twitter"->s
          </a>
        </li>
        <li className=base>
          <a
            href="https://discord.gg/reasonml"
            rel="noopener noreferrer"
            target="_blank"
            className=extLink>
            "Discord"->s
          </a>
        </li>
        <li className=base>
          <a
            href="https://github.com/reason-association/reasonml.org"
            rel="noopener noreferrer"
            target="_blank"
            className=extLink>
            "Github"->s
          </a>
        </li>
      </ul>
    </div>;
  };
};

/* isOverlayOpen: if the mobile overlay is toggled open */
[@react.component]
let make = (~overlayState: (bool, (bool => bool) => unit)) => {
  let minWidth = "20rem";
  let router = Next.Router.useRouter();

  let route = router.route;

  let (collapsibles, setCollapsibles) =
    React.useState(_ =>
      [|
        {
          title: "Docs",
          href: "/docs",
          children: route => {
            <SubNav.DocsLinks route />;
          },
          state: Closed,
        },
        {
          title: "API",
          href: "/apis",
          children: route => <SubNav.ApiLinks route />,
          state: Closed,
        },
      |]
    );

  let (isOverlayOpen, setOverlayOpen) = overlayState;

  let toggleOverlay = () => {
    setOverlayOpen(prev => !prev);
  };

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

  let nonCollapsibleOnMouseEnter = evt => {
    ReactEvent.Mouse.preventDefault(evt);
    resetCollapsibles();
  };

  // Client side navigation requires us to reset the collapsibles
  // whenever a route change had occurred, otherwise the collapsible
  // will stay open, even though you clicked a link
  React.useEffect1(
    () => {
      open Next.Router.Events;
      let {Next.Router.events} = router;

      let onChangeComplete = _url => {
        resetCollapsibles();
        setOverlayOpen(_ => false);
      };

      events->on(`routeChangeComplete(onChangeComplete));
      events->on(`hashChangeComplete(onChangeComplete));

      Some(
        () => {
          events->off(`routeChangeComplete(onChangeComplete));
          events->off(`hashChangeComplete(onChangeComplete));
        },
      );
    },
    [||],
  );

  <nav
    ref={ReactDOMRe.Ref.domRef(outerRef)}
    id="header"
    style={Style.make(~minWidth, ())}
    className="fixed flex justify-center z-20 top-0 w-full h-18 bg-night-dark shadow text-white-80 text-base">
    <div
      className="flex justify-between mx-4 md:mx-8 items-center h-full w-full max-w-1280">
      <div className="h-10 w-10">
        <a href="/">
          <img
            className="inline-block w-full h-full"
            src="/static/reason_logo.svg"
          />
        </a>
      </div>
      /* Desktop horizontal navigation */
      <div
        className="flex sm:justify-between bg-night-dark w-10/12 sm:w-9/12 sm:h-auto sm:relative">
        <div
          className="flex justify-between w-2/4 xs:w-3/4 sm:w-full max-w-sm"
          style={Style.make(~minWidth="12rem", ())}>
        </div>
      </div>
    </div>
  </nav>;
};
