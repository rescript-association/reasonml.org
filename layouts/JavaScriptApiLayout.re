%raw
"require('../styles/main.css')";

%raw
{|
let hljs = require('highlight.js/lib/highlight');
let reasonHighlightJs = require('reason-highlightjs');
hljs.registerLanguage('reason', reasonHighlightJs);
|};

module Link = Next.Link;

module Sidebar = SidebarLayout.Sidebar;
module ApiMd = SidebarLayout.ApiMd;

/* Used for API docs (structured data) */
module Docs = {
  [@genType]
  [@react.component]
  let make = (~theme=`Reason, ~components=ApiMd.components, ~children) => {
    let router = Next.Router.useRouter();

    let categories: array(Sidebar.Category.t) = [|
      {name: "Introduction", items: [|{name: "Overview", href: "/api"}|]},
      {
        name: "JavaScript",
        items: [|
          {name: "Js Module", href: "/js_docs"},
          {name: "Belt Stdlib", href: "/belt_docs"},
        |],
      },
    |];

    let theme = ColorTheme.toCN(theme);
    let minWidth = ReactDOMRe.Style.make(~minWidth="20rem", ());
    <div>
      <div className={"text-night max-w-4xl w-full " ++ theme} style=minWidth>
        <Navigation.ApiDocs route={router##route} />
        <div className="flex">
          <Sidebar categories route={router##route} />
          <main className="pt-12 static min-h-screen overflow-visible">
            <Mdx.Provider components>
              <div className="pl-8 max-w-md mb-32 text-lg"> children </div>
            </Mdx.Provider>
          </main>
        </div>
      </div>
    </div>;
  };
};

/*
 This layout is used for structured prose text with proper H2 headings.
 We cannot really use the same layout as with the Docs module, since they
 have different semantic styling and do things such as hiding the text
 of H2 nodes.
 */
module Prose = {
  [@genType]
  [@react.component]
  let make = (~children) => {
    <Docs components=SidebarLayout.ProseMd.components> children </Docs>;
  };
};
