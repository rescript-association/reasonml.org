module Head = Next.Head;
open Util.ReactStuff;

[@react.component]
let make = (~title) => {
  <Head>
    <meta charSet="ISO-8859-1" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, minimal-ui"
    />
    <title> title->s </title>
  </Head>;
};