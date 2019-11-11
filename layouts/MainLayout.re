%raw
"require('../styles/main.css')";

module Link = Next.Link;

[@react.component]
let make = (~children) => {
  let router = Next.Router.useRouter();
  let minWidth = ReactDOMRe.Style.make(~minWidth="20rem", ());
  let (isOpen, setIsOpen) = React.useState(() => false);

  <>
    <Meta />
    <div className="mb-32">
      <div className="max-w-4xl w-full lg:w-3/4 text-night font-base">
        <Navigation
          isOpen
          toggle={() => setIsOpen(prev => !prev)}
          route={router##route}
        />
        <main
          style=minWidth
          className={"mt-24 mx-4 max-w-lg" ++ (isOpen ? " hidden" : "")}>
          <Mdx.Provider components=Mdx.Components.default>
            children
          </Mdx.Provider>
        </main>
      </div>
    </div>
  </>;
};
