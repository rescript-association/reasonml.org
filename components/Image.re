open Util.ReactStuff;

[@react.component]
let default = (~src: string, ~withShadow=false, ~caption: option(string)=?) => {
  <div className="mt-8 mb-12 md:-mx-16">
    <a href=src target="_blank" rel="noopener noreferrer">
    <img className="w-full shadow-md" src />
    </a>
    {switch (caption) {
     | None => React.null
     | Some(caption) =>
       <div className="mt-4 text-14 text-night-light md:ml-16">
         caption->s
       </div>
     }}
  </div>;
};
