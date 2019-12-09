/*
    This is the master layout for displaying sidebar based API docs.
    Most of the modules defined in here are here to be reused
    in other API related layouts, such as the Markdown representation
    or the Sidebar component.
 */

%raw
"require('../styles/main.css')";

%raw
{|
let hljs = require('highlight.js/lib/highlight');
let reasonHighlightJs = require('reason-highlightjs');
hljs.registerLanguage('reason', reasonHighlightJs);
|};

open Util.ReactStuff;
open Text;
module Link = Next.Link;

/*
    We use some custom markdown styling for the Belt docs to make
    it easier on the eyes
 */
module ApiMd = {
  module Anchor = {
    [@react.component]
    let make = (~id: string) => {
      let style =
        ReactDOMRe.Style.make(~position="absolute", ~top="-7rem", ());
      <span className="relative">
        <a className="mr-2 hover:cursor-pointer" href={"#" ++ id}>
          {j|#|j}->s
        </a>
        <a style id />
      </span>;
    };
  };

  module InvisibleAnchor = {
    [@react.component]
    let make = (~id: string) => {
      let style =
        ReactDOMRe.Style.make(~position="absolute", ~top="-1rem", ());
      <span className="relative" ariaHidden=true> <a id style /> </span>;
    };
  };

  module H1 = {
    [@react.component]
    let make = (~children) => {
      <h1
        className="text-6xl tracking-tight leading-1 font-overpass font-black text-night-dark">
        children
      </h1>;
    };
  };

  module H2 = {
    // We will currently hide the headline, to keep the structure,
    // but having an Elm like documentation
    [@react.component]
    let make = (~children) => {
      <>
        // Here we know that children is always a string (## headline)
        <InvisibleAnchor id={children->Unsafe.elementAsString} />
        <div className="border-b border-gray-200 my-20" />
        /*
         <h2
           className="inline text-xl leading-3 font-overpass font-medium">
           <Anchor id={children->Unsafe.elementAsString} />
         </h2>
         */
      </>;
    };
  };

  module Pre = {
    [@react.component]
    let make = (~children) => {
      <pre className="mt-2 mb-4 block"> children </pre>;
    };
  };

  module P = {
    [@react.component]
    let make = (~children) => {
      <p className="mt-3 leading-4 text-night"> children </p>;
    };
  };

  let components =
    Mdx.Components.t(
      ~p=P.make,
      ~li=Md.Li.make,
      ~h1=H1.make,
      ~h2=H2.make,
      ~h3=H3.make,
      ~h4=H4.make,
      ~h5=H5.make,
      ~ul=Md.Ul.make,
      ~ol=Md.Ol.make,
      ~a=Md.A.make,
      ~pre=Pre.make,
      ~inlineCode=Md.InlineCode.make,
      ~code=Md.Code.make,
      (),
    );
};

module ProseMd = {
  module Anchor = {
    [@react.component]
    let make = (~id: string) => {
      let style =
        ReactDOMRe.Style.make(~position="absolute", ~top="-7rem", ());
      <span style={ReactDOMRe.Style.make(~position="relative", ())}>
        <a className="mr-2 hover:cursor-pointer" href={"#" ++ id}>
          {j|#|j}->s
        </a>
        <a style id />
      </span>;
    };
  };

  module H2 = {
    [@react.component]
    let make = (~children) => {
      <>
        // Here we know that children is always a string (## headline)
        <h2
          className="mt-12 text-3xl leading-1 tracking-tight font-overpass font-medium font-black text-night-dark">
          <Anchor id={children->Unsafe.elementAsString} />
          children
        </h2>
      </>;
    };
  };

  module Pre = {
    [@react.component]
    let make = (~children) => {
      <pre className="mt-2 mb-4 block"> children </pre>;
    };
  };

  module P = {
    [@react.component]
    let make = (~children) => {
      <p className="text-base mt-3 leading-4 text-night"> children </p>;
    };
  };

  let components =
    Mdx.Components.t(
      ~p=P.make,
      ~li=Md.Li.make,
      ~h1=ApiMd.H1.make,
      ~h2=H2.make,
      ~h3=H3.make,
      ~h4=H4.make,
      ~h5=H5.make,
      ~ul=Md.Ul.make,
      ~ol=Md.Ol.make,
      ~a=Md.A.make,
      ~pre=Pre.make,
      ~inlineCode=Md.InlineCode.make,
      ~code=Md.Code.make,
      (),
    );
};

module Sidebar = {
  module Title = {
    [@react.component]
    let make = (~children) => {
      let className = "font-sans font-black text-night-dark text-xl mt-5";

      <div className> children </div>;
    };
  };

  module NavItem = {
    // Navigation point information
    type t = {
      name: string,
      href: string,
    };
    [@react.component]
    let make =
        (
          ~isItemActive: t => bool=_nav => false,
          ~isHidden=false,
          ~items: array(t),
        ) => {
      <ul className="ml-2 mt-1 text-night">
        {Belt.Array.map(
           items,
           m => {
             let hidden = isHidden ? "hidden" : "block";
             let active =
               isItemActive(m)
                 ? {j| bg-primary-15 text-primary-dark rounded -mx-2 px-2 font-bold block |j}
                 : "";
             <li
               key={m.name}
               className={hidden ++ " leading-5 w-4/5"}
               // to make non-interactive elements (like div, span or li) tab-able
               // see https://developer.mozilla.org/en-US/docs/Web/Accessibility/Keyboard-navigable_JavaScript_widgets
               tabIndex=0>
               <Link href={m.href}>
                 <a
                   className={
                     "block h-8 md:h-auto text-night hover:text-primary "
                     ++ active
                   }>
                   m.name->s
                 </a>
               </Link>
             </li>;
           },
         )
         ->ate}
      </ul>;
    };
  };

  module Category = {
    type t = {
      name: string,
      items: array(NavItem.t),
    };

    [@react.component]
    let make = (~isItemActive: option(NavItem.t => bool)=?, ~category: t) => {
      <div key={category.name} className="my-12">
        <Title> category.name->s </Title>
        <NavItem ?isItemActive items={category.items} />
      </div>;
    };
  };

  module UrlPath = {
    /*
        Example base: /apis/javascript
        Example route: /apis/javascript/latest/belt/something/mutable-map-int

        would parse into following `t`:
        {
         base: "/apis/javascript/latest",
         version: "latest",
         relPaths: [|"something"|],
         up: Some("belt"),
         current: "mutable-map-int"
        }
     */
    type t = {
      base: string,
      version: string,
      relPaths: array(string),
      up: option(string),
      current: option(string),
    };

    let parse = (~base: string, route: string): option(t) => {
      let allPaths =
        Js.String2.replace(route, base ++ "/", "")->Js.String2.split("/");

      Js.log(allPaths);
      let total = Belt.Array.length(allPaths);
      if (total < 2) {
        None;
      } else {
        let version = Belt.Array.getExn(allPaths, 0);
        let (up, current) =
          switch (Js.Array2.slice(allPaths, ~end_=total, ~start=-2)) {
          | [|up, current|] =>
            let up = up === version ? None : Some(up);
            (up, Some(current));
          | _ => (None, None)
          };

        let relPaths = Js.Array.slice(allPaths, ~start=1, ~end_=-2);

        Some({base, relPaths, version, up, current});
      };
    };

    /* Beautifies current titles from the url representation */
    let prettyString = (str: string) => {
      Util.String.(str->camelCase->capitalize);
    };

    let fullUpLink = (urlPath: t): string => {
      let {base, up, version} = urlPath;
      base
      ++ "/"
      ++ version
      ++ up->Belt.Option.mapWithDefault("", str => "/" ++ str);
    };
  };

  module ToplevelNav = {
    [@react.component]
    let make = (~title="", ~backHref=?, ~version=?) => {
      let back =
        switch (backHref) {
        | Some(href) => <Link href> <a> "<-"->s </a> </Link>
        | None => React.null
        };

      let versionTag =
        switch (version) {
        | Some(version) => <Tag kind=`Subtle> version </Tag>
        | None => React.null
        };

      <div className="flex"> back <Title> title->s </Title> versionTag </div>;
    };
  };

  module CollapsibleSection = {
    module NavUl = {
      // Navigation point information
      type t = {
        name: string,
        href: string,
      };

      [@react.component]
      let make = (~isItemActive: t => bool=_nav => false, ~items: array(t)) => {
        <ul className="mt-3 text-night">
          {Belt.Array.map(
             items,
             m => {
               let active =
                 isItemActive(m)
                   ? {j| bg-primary-15 text-primary-dark -ml-1 px-2 font-bold block |j}
                   : "";
               <li
                 key={m.name}
                 className="leading-5 w-4/5"
                 // to make non-interactive elements (like div, span or li) tab-able
                 // see https://developer.mozilla.org/en-US/docs/Web/Accessibility/Keyboard-navigable_JavaScript_widgets
                 tabIndex=0>
                 <a
                   href={m.href}
                   className={
                     "block pl-3 h-8 md:h-auto border-l-2 border-night-10 block text-night hover:pl-4 hover:text-night-dark"
                     ++ active
                   }>
                   m.name->s
                 </a>
               </li>;
             },
           )
           ->ate}
        </ul>;
      };
    };
    [@react.component]
    let make =
        (~isItemActive=?, ~headers: array(string), ~moduleName: string) => {
      let (collapsed, setCollapsed) = React.useState(() => false);
      let items =
        Belt.Array.map(headers, header =>
          NavUl.{name: header, href: "#" ++ header}
        );

      let direction = collapsed ? `Down : `Up;

      <div className="py-3 px-3 bg-primary-15 rounded-lg">
        <a
          className="flex justify-between items-center cursor-pointer text-primary hover:text-primary text-night-dark text-base"
          href="#"
          onClick={evt => {
            ReactEvent.Mouse.preventDefault(evt);
            setCollapsed(isCollapsed => !isCollapsed);
          }}>
          moduleName->s
          <span className="ml-2 block text-primary">
            <Icon.Caret size=`Md direction />
          </span>
        </a>
        {if (!collapsed) {
           <NavUl ?isItemActive items />;
         } else {
           React.null;
         }}
      </div>;
    };
  };

  module MobileNavButton = {
    [@react.component]
    let make = (~hidden: bool, ~onClick) => {
      <button
        className={
          (hidden ? "hidden" : "md:hidden")
          ++ " bg-primary rounded-full w-12 h-12 fixed bottom-0 right-0 mr-8 mb-8"
        }
        onMouseDown=onClick
      />;
    };
  };

  // subitems: list of functions inside given module (defined by route)
  [@react.component]
  let make =
      (
        ~categories: array(Category.t),
        ~route: string,
        ~preludeSection=React.null,
      ) => {
    let isItemActive = (navItem: NavItem.t) => {
      navItem.href === route;
    };

    /* Used for mobile sidebar navigation */
    let (isOpen, setIsOpen) = React.useState(() => true);

    <>
      <div
        className={
          (isOpen ? "fixed z-10" : "hidden")
          ++ " h-auto w-full overflow-y-visible bg-white md:relative md:block md:w-1/4 md:bg-white-80"
        }>
        <aside
          className="relative top-0 px-4 w-full block md:sticky md:top-16 border-r border-snow-dark h-screen overflow-y-auto scrolling-touch pb-24">
          <div> preludeSection </div>
          /* Firefox ignores padding in scroll containers, so we need margin
               to make a bottom gap for the sidebar.
               See https://stackoverflow.com/questions/29986977/firefox-ignores-padding-when-using-overflowscroll
             */
          <div className="mb-56">
            {categories
             ->Belt.Array.map(category =>
                 <div key={category.name}>
                   <Category isItemActive category />
                 </div>
               )
             ->ate}
          </div>
        </aside>
      </div>
      <MobileNavButton
        hidden=isOpen
        onClick={evt => {
          ReactEvent.Mouse.preventDefault(evt);
          setIsOpen(prev => !prev);
        }}
      />
    </>;
  };
};

[@react.component]
let make =
    (
      ~theme: ColorTheme.t,
      ~components=ApiMd.components,
      ~sidebar: React.element,
      ~route: string,
      ~children,
    ) => {
  let (isOpen, setIsOpen) = React.useState(() => false);

  let theme = ColorTheme.toCN(theme);

  <>
    <Meta />
    <div className={"mt-16 " ++ theme}>
      <div className="w-full text-night font-base">
        <Navigation
          isOverlayOpen=isOpen
          toggle={() => setIsOpen(prev => !prev)}
          route
        />
        <div className="flex justify-center">
          <div className="min-w-20 lg:align-center w-full max-w-xl">
            <Mdx.Provider components>
              <div className="flex">
                sidebar
                <div className="flex justify-center md:w-3/4">
                  <main className="w-5/6 pt-8 mb-32 text-lg"> children </main>
                </div>
              </div>
            </Mdx.Provider>
          </div>
        </div>
      </div>
    </div>
  </>;
};
