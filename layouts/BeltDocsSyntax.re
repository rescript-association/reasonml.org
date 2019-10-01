module Syntax = {
  type t =
    | Reason
    | OCaml
    | Other;

  let toReadableString =
    fun
    | Reason => "RE"
    | OCaml => "ML"
    | Other => "Other";
};

type t = {
  syntax: Syntax.t,
  setSyntax: Syntax.t => unit,
  refmt: (~lang: string, ~meta: string=?, string) => string,
};

let defaultValue = {
  syntax: Reason,
  setSyntax: _ => (),
  refmt: (~lang as _, ~meta as _=?, src) => src,
};

let ctx = React.createContext(defaultValue);

module ContextProvider = {
  [@bs.obj]
  external makeProps:
    (~key: string=?, ~value: t, ~children: React.element, unit) =>
    {
      .
      "value": t,
      "children": React.element,
    } =
    "";
  let make = React.Context.provider(ctx);
};

let useContext = () => React.useContext(ctx);

module Provider = {
  [@react.component]
  let make = (~children) => {
    let (syntax, setSyntax) = React.useState(() => Syntax.Reason);

    <ContextProvider
      value={
        syntax,
        setSyntax: syntax => setSyntax(_ => syntax),
        refmt: (~lang, ~meta=?, src) =>
          Syntax.(
            switch (lang, meta, syntax) {
            | ("re" | "reason", Some("sig"), OCaml) =>
              src->Refmt.parseREI->Refmt.printMLI
            | ("re" | "reason", _, OCaml) => src->Refmt.parseRE->Refmt.printML
            | ("ml" | "ocaml", Some("sig"), Reason) =>
              src->Refmt.parseMLI->Refmt.printREI
            | ("ml" | "ocaml", _, Reason) =>
              src->Refmt.parseMLI->Refmt.printREI
            | _ => src
            }
          ),
      }>
      children
    </ContextProvider>;
  };
};
