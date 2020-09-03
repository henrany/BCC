datatype exp = 
            Const of int
        |   Prim of string * exp*exp
        |   Var of string
        |   Let of string * exp * exp;
        
val e1 = Let("z", Const 17, Prim("+", Var "z", Var "z"));
        

exception NonClosed;

fun lookup [] id = raise NonClosed
  | lookup ((k:string, v)::t) id = if k = id then v else lookup t id;

fun eval (e:exp) (st: (string * exp) list) : int = 
        case e of 
            (Const i) => i
        |   (Var v) => eval (lookup st v) st
        |   (Prim(f, e1, e2)) =>
               let
                   val v1 = (eval e1 st)
                   val v2 = (eval e2 st)
               in
               case f of 
                 ("+") => v1 + v2
               |   ("-") => v1 - v2
               |   ("*") => v1 * v2
               |   ("/") => v1 div v2
               |   ("%") => v1 mod v2
               |    _    => raise Match
               end
        |    (Let(x, e1, e2)) =>
               let 
               val v = eval e1 st
               val st' = (x, Const v) :: st; 
               in 
                eval e2 st'         
        end

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
                                                  Prim("+",Const 20, 
                                                                  Prim("*",Var "a", Var "b")
                                                        )
                                    ), 
                        Var "x")
        );
                                        

eval a [];
eval b [];
eval c [];
eval d [];
eval e [];