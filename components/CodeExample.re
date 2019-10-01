open Util.ReactStuff;

[@react.component]
let make = (~children, ~syntax: BeltDocsSyntax.Syntax.t) => {
  <div className="flex flex-col rounded-lg bg-sand-lighten-20 py-4 px-6 mt-6">
    <div
      className="flex justify-between font-overpass text-main-lighten-20 font-bold text-sm mb-3">
      "Example"->s
      <span className="font-montserrat text-primary-lighten-50">
        {syntax->BeltDocsSyntax.Syntax.toReadableString->s}
      </span>
    </div>
    children
  </div>;
};
