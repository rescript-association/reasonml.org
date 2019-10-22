type rawModule;
type parsedMdxModule = {
[@dead "parsedMdxModule.id"]   id: string, /* Id, which is also part of the Url */
[@dead "parsedMdxModule.filepath"]   filepath: string,
};

[@bs.deriving abstract]
type webpackCtx = {keys: unit => array(string)};

[@dead "getMdxModule"] let getMdxModule: (webpackCtx, string) => rawModule = [%raw
  (ctx, filepath) => "{ return ctx(filepath); }"
];

[@dead "beltCtx"] let beltCtx: webpackCtx = [%raw
  "require.context('../pages/belt_docs', true, /^\.\/.*\.mdx$/)"
];

[@dead "toMdxModules"] let toMdxModules = (ctx: webpackCtx): array(parsedMdxModule) =>
  ctx
  ->keysGet()
  ->Belt.Array.map(filepath => {
      let id =
        switch (Js.String.match([%re "/\\.\\/(.*)\\.mdx/"], filepath)) {
        | Some([|_, id|]) => id
        | _ => filepath
        };

      let correctedFilepath =
        Js.String.replaceByRe([%re "/^\\.\\//"], "./pages/belt/", filepath);

      /*let m = ctx->getMdxModule(filepath);*/

      {id, filepath: correctedFilepath};
    });

[@dead "getAllBeltModules"] let getAllBeltModules = () => {
  beltCtx->toMdxModules;
};