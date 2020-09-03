datatype exp =
         Const of int
         | Prim2 of string * exp * exp
         | Prim1 of string * exp
         | Ite of exp * exp * exp
         | Var of string
         | Let of string * exp * exp
         | LetFun of string * string * exp * exp
         | Call of exp * exp;

type 'v env = (string * 'v) list;

datatype value =
         Int of int
         | Closure of string * string * exp * value env;
         
exception NonClosed;
exception EvalError;
exception PrimError;

fun intToBool 1 = true
  | intToBool 0 = false
  | intToBool _ = raise Match;

fun lookup [] id = raise NonClosed
  | lookup ((k:string, v)::t) id = if k = id then v else lookup t id;

fun eval (e:exp) (st: (string * value) list) : int =
    case e of
        (Const i) => i
      | (Var v) =>
        let val vv = lookup st v in
            case vv of
                (Int i) => i
              | _ => raise EvalError
        end
      | (Prim2(f, e1, e2)) =>
        let
            val v1 = (eval e1 st);
            val v2 = (eval e2 st) in
        case f of
            ("+") => v1 + v2
          | ("-") => v1 - v2
          | ("*") => v1 * v2
          | ("/") => v1 div v2
          | ("%") => v1 mod v2
          | ("=") => if v1 = v2 then 1 else 0
          | _ => raise PrimError
        end
      | (Ite(c, t, e)) => if (intToBool (eval c st)) then eval t st else eval e st
      | (Let(x, e1, e2)) => eval e2 ((x, Int (eval e1 st))::st)
      | (LetFun(f, x, e1, e2)) => eval e2 ((f, Closure(f, x, e1, st))::st)
      | (Call(Var f, e)) =>
        let val fv = (lookup st f) in
            case fv of
                (Closure(f, x, e1, fSt)) =>
                let
                    val ev = Int(eval e st);
                    val st' = (x, ev) :: (f, fv) :: fSt
                in
                    eval e1 st'
                end
             | _ => raise EvalError
        end
      | _ => raise Match;
      

val a = Let("a", Const 5,
             LetFun("f", "x", Prim2("+", Var "x", Var "a"),
                    Let("a", Const 3,
                        Call(Var "f", Const 1)
                       )
            ));

val b = Let("a", Const 5,
             LetFun("f", "x", Prim2("/", Var "x", Var "a"),
                    Let("a", Const 3,
                        Call(Var "f", Const 20)
                       )
            ));
val c = Let("b", Const 3,
             LetFun("f", "x", Prim2("%", Var "x", Var "b"),
                    Let("b", Const 2,
                        Call(Var "f", Const 10)
                       )
            ));

eval a [];
eval b [];
eval c [];
