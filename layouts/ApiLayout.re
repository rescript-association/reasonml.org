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

module MainMd = {
  module P = {
    [@react.component]
    let make = (~children) => {
      <p className="text-xl mt-3 leading-4 text-night-dark"> children </p>;
    };
  };

  module H1 = {
    [@react.component]
    let make = (~children) => {
      <h1 className="text-7xl font-overpass font-black text-night-dark">
        children
      </h1>;
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
      ~pre=Md.Pre.make,
      ~inlineCode=Md.InlineCode.make,
      ~code=Md.Code.make,
      (),
    );
};
module Category = {
  module Card = {
    type t = {
      title: string,
      descr: string,
      href: option(string),
      src: string,
    };
    [@react.component]
    let make = (~card: t) => {
      let element =
        <>
          <img src={card.src} className="w-full mb-2" />
          <h3 className="font-overpass font-black text-3xl text-night-dark">
            card.title->s
          </h3>
          <div className="text-base leading-5 text-night"> card.descr->s </div>
        </>;

      <div className="w-1/4">
        {switch (card.href) {
         | Some(href) => <Link href> <a> element </a> </Link>
         | None =>
           <div className="opacity-50" title="Not available yet">
             element
           </div>
         }}
      </div>;
    };
  };

  type t = {
    name: string,
    cards: array(Card.t),
  };

  [@react.component]
  let make = (~category: t) => {
    <div className="border-t border-snow-dark pt-8">
      <h2 className="mb-8 font-black text-6xl text-night-dark">
        category.name->s
      </h2>
      <div className="flex flex-wrap justify-between">
        {Belt.Array.map(category.cards, card => <Card key={card.title} card />)
         ->ate}
      </div>
    </div>;
  };
};

let categories: array(Category.t) = [|
  {
    name: "JavaScript",
    cards: [|
      {
        title: "Js Module",
        descr: "Bindings for Common Browser APIs",
        src: "/static/api-img-js.svg",
        href: Some("/apis/javascript/latest/js"),
      },
      {
        title: "Belt Module",
        descr: "The Reason Standard Library for the Web",
        src: "/static/api-img-belt.svg",
        href: Some("/apis/javascript/latest/belt"),
      },
      {
        title: "Node Module",
        descr: "Simple Bindings for the NodeJS API",
        src: "/static/api-img-nodejs.svg",
        href: None,
      },
    |],
  },
|];

/* Used for API docs (structured data) */
[@react.component]
let make = (~children) => {
  let router = Next.Router.useRouter();
  let (isOpen, setIsOpen) = React.useState(() => false);

  let theme = ColorTheme.toCN(`Reason);
  let minWidth = ReactDOMRe.Style.make(~minWidth="20rem", ());
  <div>
    <div className={"max-w-4xl w-full " ++ theme} style=minWidth>
      <Navigation
        isOpen
        toggle={() => setIsOpen(prev => !prev)}
        route={router##route}
      />
      <div className="flex mt-16">
        <main
          className="pt-12 flex justify-center w-4/5 static min-h-screen overflow-visible">
          <div className="flex flex-col">
            <Mdx.Provider components=MainMd.components>
              <div className="max-w-md mb-32 text-lg"> children </div>
            </Mdx.Provider>
            <div>
              {Belt.Array.map(categories, category =>
                 <div key={category.name} className="pb-16">
                   <Category category />
                 </div>
               )
               ->ate}
            </div>
          </div>
        </main>
      </div>
    </div>
  </div>;
};
