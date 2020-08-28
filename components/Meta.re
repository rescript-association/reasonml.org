open Util.ReactStuff;
module Head = Next.Head;

let ogImgDefault = "https://res.cloudinary.com/dmm9n7v9f/image/upload/v1588077512/Reason%20Association/reasonml.org/reasonml-org-social-default_re6vor.jpg";

/*
    canonical: Set a canonical URL pointing to the original content.
 */
[@react.component]
let make =
    (
      ~siteName="reasonml.org (deprecated)",
      ~keywords: array(string)=[||],
      ~description="Site moved to rescript-lang.org",
      ~canonical=?,
      ~title=?,
    ) => {
  let title =
    switch (title) {
    | None
    | Some("") => siteName
    | Some(title) => title
    };

  <Head>
    <title key="title"> title->s </title>
    <meta charSet="utf-8" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, minimal-ui"
    />
    <meta key="description" name="description" content=description />
    <meta
      key="keywords"
      name="keywords"
      content={Js.Array2.joinWith(keywords, ",")}
    />
    {switch (canonical) {
     | Some(href) => <link key="canonical" href rel="canonical" />
     | None => React.null
     }}
    <link
      key="icon"
      rel="icon"
      sizes="16x16 32x32 64x64"
      href="/static/favicon.ico"
    />
  </Head>;
};
