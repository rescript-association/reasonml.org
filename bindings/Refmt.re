type astAndComments;

[@bs.module "reason"] external parseRE: string => astAndComments = "parseRE";
[@bs.module "reason"] external parseREI: string => astAndComments = "parseREI";
[@bs.module "reason"] external printRE: astAndComments => string = "printRE";
[@bs.module "reason"] external printREI: astAndComments => string = "printREI";

[@bs.module "reason"] external parseML: string => astAndComments = "parseML";
[@bs.module "reason"] external parseMLI: string => astAndComments = "parseMLI";
[@bs.module "reason"] external printML: astAndComments => string = "printML";
[@bs.module "reason"] external printMLI: astAndComments => string = "printMLI";
