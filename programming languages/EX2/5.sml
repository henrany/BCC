datatype exp = 
            Const of int
        |   Prim of string * exp*exp
        |   Var of string
        |   Let of string * exp * exp;
        
val e1 = Let("z", Const 17, Prim("+", Var "z", Var "z"));
        

exception NonClosed;

fun lookup [] id = raise NonClosed
  | lookup ((k:string, v)::t) id = if k = id then v else lookup t id;

fun calculaFechada (e:exp) (st: (string * exp) list) : int = 
        case e of 
            (Const i) => i
        |   (Var v) => calculaFechada (lookup st v) st
        |   (Prim(f, e1, e2)) =>
               let
                   val v1 = (calculaFechada e1 st)
                   val v2 = (calculaFechada e2 st)
               in
               case f of 
                 ("+") => v1 + v2
               |   ("-") => v1 - v2
               |   ("*") => v1 * v2
               |   ("/") => v1 div v2
               |   ("%") => v1 mod v2
               |    _    => raise Match
               end
        |   (Let(x, e1, e2)) => calculaFechada e2 ((x, Const (calculaFechada e1 st)) :: st)

val a = Let("z", Const 200,Prim("/",Var "z", Const 10));
val b = Let("x",Const 10,
                         Prim("%", 
                              Let("x", Const 50,
                                    Prim("+",Var "x",Var "x")),Const 3
                                )
                        );
val c = Let("y", Const 2,
                        Prim("-",
                            Let("z", Const 15,
                                    Prim("*",Var "z", Var "y")),
                                    Const 10)
                        );
val d = Let("a", Const 20,
                         Prim("+", 
                                  Let("a", Const 15,
                                        Prim("*",Const 10, Var "a")), Var "a"
                                        
                                    )
            );
            
val e = Let("b", Const 50,
                         Prim("+", 
                                  Let("x", Const 20,
                                                  Prim("+",Var "x", 
                                                                  Prim("*",Var "a", Var "b")
                                                        )
                                    ), 
                       Const 20)
        );
calculaFechada a [];
calculaFechada b [];
calculaFechada c [];
calculaFechada d [];
calculaFechada e [("a",Const 3)];