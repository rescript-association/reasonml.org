module Flavour = {
  type t =
    | Reason
    | OCaml
    | Other;

  let toReadableString =
    fun
    | Reason => "RE"
    | OCaml => "ML"
    | Other => "Other";

  let fromString =
    fun
    | "re"
    | "reason" => Reason
    | "ml"
    | "ocaml" => OCaml
    | _ => Other;
};

type t = {
  flavour: Flavour.t,
  setFlavour: Flavour.t => unit,
  refmt: (~lang: string, string) => string,
};

let defaultValue = {
  flavour: Reason,
  setFlavour: _ => (),
  refmt: (~lang as _, src) => src,
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
    let (flavour, setFlavour) = React.useState(() => Flavour.Reason);

    <ContextProvider
      value={
        flavour,
        setFlavour: flavour => setFlavour(_ => flavour),
        refmt: (~lang, src) => {
          let exampleFlavour = Flavour.fromString(lang);
          Flavour.(
            switch (exampleFlavour, flavour) {
            | (Reason, OCaml) => src->Refmt.parseRE->Refmt.printML
            | (OCaml, Reason) => src->Refmt.parseML->Refmt.printRE
            | (_, _) => src
            }
          );
        },
      }>
      children
    </ContextProvider>;
  };
};
