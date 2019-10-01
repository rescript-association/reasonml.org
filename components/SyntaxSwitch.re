open BeltDocsSyntax;

[@react.component]
let make = () => {
  let syntaxContext = useContext();

  let isActive = syntax =>
    syntaxContext.syntax == syntax ? "bg-white text-black" : "text-white";

  <div
    className="flex justify-between ml-4 border border-white rounded shadow">
    <span
      className={"p-2 " ++ isActive(Syntax.Reason)}
      onClick={_ => syntaxContext.setSyntax(Syntax.Reason)}>
      {React.string("Reason")}
    </span>
    <span
      className={"p-2 " ++ isActive(Syntax.OCaml)}
      onClick={_ => syntaxContext.setSyntax(Syntax.OCaml)}>
      {React.string("OCaml")}
    </span>
  </div>;
};
