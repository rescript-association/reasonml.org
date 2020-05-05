// This is a server-side function for exposing the RSS feed as a text/xml resource

// The implementation was inspired by this gist:
// https://gist.github.com/fredrikbergqvist/36704828353ebf5379a5c08c7583fe2d

// We need to keep that empty React component, otherwise getServerSideProps will complain
[@react.component]
let default = () => {
  ();
};

type props = Js.t({.});
type params = Js.t({.});

let getServerSideProps: Next.GetServerSideProps.t(props, params) =
  ctx => {
    open Next.GetServerSideProps;
    let {res} = ctx;

    let content = BlogApi.RssFeed.(getLatest()->toXmlString);

    res->Res.setHeader("Content-Type", "text/xml");
    res->Res.write(content);
    res->Res.end_;

    let ret = {"props": Js.Obj.empty()};
    Promise.resolved(ret)->Promise.Js.toBsPromise;
  };
