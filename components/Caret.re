type direction = [ | `Up | `Down];

[@react.component]
let make = (~direction: direction) => {
  <svg className="stroke-current" x="0px" y="0px" viewBox="0 0 14.5 7.1">
    {switch (direction) {
     | `Up =>
       <path strokeWidth="2.5" fill="none" d="M0.7,6.1l6.5-4.5l6.5,4.5" />
     | `Down => <path strokeWidth="2.5" fill="none" d="M13.8,1.1L7.2,5.6L0.8,1.1" />
     }}
  </svg>;
};
