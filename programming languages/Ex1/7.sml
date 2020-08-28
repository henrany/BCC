(*the datatype is declared as real since we are dealing with length and from intiution , length is alway in decimal figures
    so the input should all be in real values*)

datatype exp = iconst of real 
               | AreaRectangle of exp*exp 
               | perimeterRectangle of exp*exp
               | AreaSquare of exp
               | perimeterSquare of exp
               | AreaTriangleRectangle of exp*exp
               | perimeterTriangleRectangle of exp*exp*exp
               | AreaCircle of exp
               | perimeterCircle of exp;
               


fun  eval(iconst b) = b
    | eval(AreaRectangle(e1,e2)) = eval(e1) * eval(e2)
    | eval(perimeterRectangle(e1,e2)) = 2.0 * (eval(e1) + eval(e2))
    | eval(AreaSquare(e1)) = eval(e1) * eval(e1)
    | eval(perimeterSquare(e1)) = 4.0*eval(e1)
    | eval(AreaTriangleRectangle(e1,e2)) = (eval(e1)*eval(e2)) / 2.0
    | eval(perimeterTriangleRectangle(e1,e2,e3)) = eval(e1) + eval(e2) + eval(e3)
    | eval(AreaCircle(e1)) = 3.142 * eval(e1) * eval(e1)
    | eval(perimeterCircle(e1)) = 2.0 * 3.142 * eval(e1);
    
(*val a = AreaRectangle(iconst 2.0, iconst 3.0);
val b = perimeterRectangle(iconst 2.0, iconst 3.0);
val c = AreaSquare(iconst 3.0);
val d = perimeterSquare(iconst 3.0);
val e = AreaTriangleRectangle(iconst 3.0, iconst 4.0);
val f = perimeterTriangleRectangle(iconst 3.0, iconst 4.0, iconst 5.0);
val g = AreaCircle(iconst 3.0);
val h = perimeterCircle(iconst 3.0);
eval a;
eval b;
eval c;
eval d;
eval e;
eval f;
eval g;
eval h;*)