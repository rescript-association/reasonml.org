open Util.ReactStuff;

type kind = [ | `Subtle];

[@react.component]
let make = (~children, ~kind=`Subtle) => {
  let className =
    switch (kind) {
    | `Subtle => "px-2 inline-block align-bottom bg-snow-dark text-night font-semibold rounded text-sm"
    };
  <div className> children->s </div>;
};
