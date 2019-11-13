open Util.ReactStuff;
module Link = Next.Link;

let link = "no-underline block text-inherit hover:cursor-pointer hover:text-white text-white-80";
let activeLink = "text-inherit font-bold text-fire-80 border-b border-fire-80";

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
        ~id: string,
        ~state: state,
        ~active=false,
        ~children,
      ) => {
    let onClick = evt => {
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
      onStateChange(~id, HoverOpen);
    };

    let isOpen =
      switch (state) {
      | Closed => false
      | KeepOpen
      | HoverOpen => true
      };

    let direction = isOpen ? `Up : `Down;

    <div className="font-bold sm:font-normal relative" onMouseEnter>
      <div className="flex items-center">
        <a
          onClick
          className={
            (active ? activeLink : link)
            ++ " font-bold"
            ++ (isOpen ? " text-white" : "")
          }>
          title->s
          <span className="fill-current inline-block ml-2 w-3 h-2">
            <Caret direction />
          </span>
        </a>
      </div>
      <div
        className={
          (isOpen ? "block" : "hidden")
          ++ " sm:fixed sm:left-0 sm:border-night sm:border-t sm:mt-5 bg-night-dark w-full h-16"
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
[@react.component]
let make = (~isOpen=false, ~toggle=() => (), ~route="/") => {
  let minWidth = "20rem";

  let (collapsibles, setCollapsibles) =
    React.useState(_ =>
      [|
        ("Docs", "Docs Items"->s, CollapsibleLink.Closed),
        ("API", "API Items"->s, CollapsibleLink.Closed),
      |]
    );

  let resetCollapsibles = () =>
    setCollapsibles(prev =>
      Belt.Array.map(
        prev,
        c => {
          let (title, children, _) = c;
          (title, children, CollapsibleLink.Closed);
        },
      )
    );

  let outerRef = React.useRef(Js.Nullable.null);
  useOutsideClick(ReactDOMRe.Ref.domRef(outerRef), resetCollapsibles);

  <nav
    ref={ReactDOMRe.Ref.domRef(outerRef)}
    id="header"
    style={Style.make(~minWidth, ())}
    className="fixed z-10 top-0 sm:pl-10 w-full h-16 bg-night-dark shadow text-white-80 sm:flex sm:justify-center text-xl sm:text-base">
    <div
      className="flex justify-between items-center h-full w-full sm:max-w-4xl">
      <div className="sm:w-3/12">
        <Link href="/">
          <a>
            <img
              className="w-24 mb-4 inline-block"
              src="/static/reason_logo.svg"
            />
          </a>
        </Link>
      </div>
      <div className="block mb-4 pr-4 sm:hidden">
        <button
          className="flex items-center px-3 py-2 border rounded text-teal-200 border-teal-400 hover:text-white hover:border-white"
          onClick={_ => toggle()}>
          <svg
            className="fill-current h-3 w-3"
            viewBox="0 0 20 20"
            xmlns="http://www.w3.org/2000/svg">
            <path d="M0 3h20v2H0V3zm0 6h20v2H0V9zm0 6h20v2H0v-2z" />
          </svg>
        </button>
      </div>
      <div
        style={Style.make(~minWidth, ())}
        className={
          (isOpen ? "flex" : "hidden")
          ++ " px-2 flex-col fixed top-0 left-0 h-full w-full bg-night-dark sm:pl-10 sm:h-auto sm:flex sm:relative sm:flex-row sm:justify-between"
        }>
        <div className="flex h-16 justify-between items-center sm:hidden">
          <Link href="/">
            <a className="w-24"> <img src="/static/reason_logo.svg" /> </a>
          </Link>
          <span
            onClick={_ => toggle()}
            className="inline-block text-center w-6 text-2xl font-bold">
            "X"->s
          </span>
        </div>
        <div
          className="flex flex-col sm:flex-row sm:justify-between sm:w-3/4 max-w-sm">
          <Link href="/try">
            <a
              className={
                linkOrActiveLink(~target="/try", ~route) ++ " font-bold"
              }>
              "Playground"->s
            </a>
          </Link>
          <Link href="/blog">
            <a
              className={
                linkOrActiveLink(~target="/blog", ~route) ++ " font-bold"
              }>
              "Blog"->s
            </a>
          </Link>
          <Link href="/community">
            <a
              className={
                linkOrActiveLink(~target="/community", ~route) ++ " font-bold"
              }>
              "Community"->s
            </a>
          </Link>
          {Belt.Array.mapWithIndex(
             collapsibles,
             (idx, c) => {
               let (title, children, state) = c;
               let onStateChange = (~id, state) =>
                 {setCollapsibles(prev =>
                    Belt.Array.map(
                      prev,
                      c => {
                        let (title, children, _) = c;
                        if (title === id) {
                          (title, children, state);
                        } else {
                          (title, children, CollapsibleLink.Closed);
                        };
                      },
                    )
                  )};
               <CollapsibleLink
                 id=title
                 onStateChange
                 key={idx->Belt.Int.toString}
                 title
                 state>
                 children
               </CollapsibleLink>;
             },
           )
           ->ate}
        </div>
        <div className="flex">
          <a
            href="https://github.com/reason-association/reasonml.org"
            rel="noopener noreferrer"
            target="_blank"
            className=link>
            <Icon.Github className="w-6 h-6" />
          </a>
          <a
            href="https://twitter.com/reasonml"
            rel="noopener noreferrer"
            target="_blank"
            className=link>
            <Icon.Twitter className="w-6 h-6" />
          </a>
          <a
            href="https://discord.gg/reasonml"
            rel="noopener noreferrer"
            target="_blank"
            className=link>
            <Icon.Discord className="w-6 h-6" />
          </a>
        </div>
        <button className="sm:border-l sm:border-r sm:border-night sm:h-full">
          <img src="/static/ic_search_small.svg" className="w-6 h-6" />
        </button>
      </div>
    </div>
  </nav>;
};

/*
     Used specifically for Api docs browsing.
     Difference here is the prominent Searchbar in the center
     and a version info shown on the side
 */
module ApiDocs = {
  [@react.component]
  let make = (~route: string, ~versionInfo=?) => {
    <nav
      id="header"
      className="fixed z-10 top-0 w-full h-16 bg-night-dark shadow flex items-center text-white-80 text-sm">
      <Link href="/">
        <a className="flex items-center w-40">
          <img src="/static/reason_logo.svg" className="h-10" />
        </a>
      </Link>
      <div
        className="ml-6 flex w-3/5 px-3 h-10 max-w-sm rounded-lg text-white bg-light-grey-20 content-center items-center w-2/3">
        <img
          src="/static/ic_search_small.svg"
          className="mr-3"
          ariaHidden=true
        />
        <input
          type_="text"
          className="bg-transparent placeholder-white-80 block focus:outline-none w-full ml-2"
          placeholder="Search not ready yet..."
        />
      </div>
      <div className="flex mx-4 text-white-80 justify-between ml-auto">
        <Link href="/api">
          <a className={linkOrActiveLink(~target="/api", ~route)}>
            "API"->s
          </a>
        </Link>
        <a
          href="https://github.com/reason-association/reasonml.org"
          rel="noopener noreferrer"
          target="_blank"
          className={link ++ " align-middle ml-6"}>
          "Github"->s
        </a>
        {switch (versionInfo) {
         | Some(version) =>
           <a
             href="https://github.com/BuckleScript/bucklescript/releases"
             rel="noopener noreferrer"
             target="_blank"
             className="bg-light-grey-20 leading-normal ml-6 px-1 rounded text-light-grey text-xs">
             version->s
           </a>
         | None => React.null
         }}
      </div>
    </nav>;
  };
};
