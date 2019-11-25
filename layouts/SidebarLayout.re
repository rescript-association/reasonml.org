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
                 ? {j| bg-primary-5 text-primary-dark rounded -ml-2 px-2 font-bold block |j}
                 : "";
             <li
               key={m.name}
               className={hidden ++ " leading-5 w-4/5"}
               // to make non-interactive elements (like div, span or li) tab-able
               // see https://developer.mozilla.org/en-US/docs/Web/Accessibility/Keyboard-navigable_JavaScript_widgets
               tabIndex=0>
               <Link href={m.href}>
                 <a
                   className={"block text-night hover:text-primary " ++ active}>
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
      <div key={category.name} className="my-12 pl-10">
        <Overline> category.name->s </Overline>
        <NavItem ?isItemActive items={category.items} />
      </div>;
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
        <ul className="mt-2 text-night">
          {Belt.Array.map(
             items,
             m => {
               let active =
                 isItemActive(m)
                   ? {j| bg-primary-5 text-primary-dark -ml-1 px-2 font-bold block |j}
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
                     "block pl-3 border-l-2 border-night-10 block text-night hover:pl-4 hover:text-night-dark"
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

      <div className="py-8 pl-10 pr-4 border-b border-snow-dark">
        <Overline>
          <a
            className="flex justify-between items-center cursor-pointer text-primary hover:text-primary font-overpass font-black text-night-dark text-xl"
            href="#"
            onClick={evt => {
              ReactEvent.Mouse.preventDefault(evt);
              setCollapsed(isCollapsed => !isCollapsed);
            }}>
            moduleName->s
            <span className="ml-2 block h-2 w-4 text-primary">
              <Caret direction />
            </span>
          </a>
        </Overline>
        {if (!collapsed) {
           <NavUl ?isItemActive items />;
         } else {
           React.null;
         }}
      </div>;
    };
  };

  // subitems: list of functions inside given module (defined by route)
  [@react.component]
  let make =
      (~categories: array(Category.t), ~route: string, ~children=React.null) => {
    let isItemActive = (navItem: NavItem.t) => {
      navItem.href === route;
    };

    <div
      className="flex w-64 h-auto overflow-y-visible block bg-white-80"
      style={Style.make(~maxWidth="17.5rem", ())}>
      <aside
        className="relative w-full sticky border-r border-snow-dark h-screen block overflow-y-auto scrolling-touch pb-32"
        style={Style.make(~top="3rem", ())}>
        <div className="bg-primary-5"> children </div>
        <div>
          {categories
           ->Belt.Array.map(category =>
               <div key={category.name}>
                 <Category isItemActive category />
               </div>
             )
           ->ate}
        </div>
      </aside>
    </div>;
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
  let minWidth = ReactDOMRe.Style.make(~minWidth="20rem", ());
  <div>
    <div className={"max-w-4xl w-full " ++ theme} style=minWidth>
      <Navigation isOpen toggle={() => setIsOpen(prev => !prev)} route />
      <div className="flex mt-12">
        sidebar
        <main className="pt-12 w-4/5 static min-h-screen overflow-visible">
          <Mdx.Provider components>
            <div className="pl-8 max-w-md mb-32 text-lg"> children </div>
          </Mdx.Provider>
        </main>
      </div>
    </div>
  </div>;
};
