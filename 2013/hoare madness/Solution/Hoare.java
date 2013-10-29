import java.util.Scanner;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Hoare {

	public static Condition pre, post;
	
	public static LinkedList<Statement> program;
	
	public static void parse (String buffer) {
		
		StringTokenizer st;
		StringTokenizer prog;
		
		st = new StringTokenizer (buffer, "{}", false);
		pre = new Condition (st.nextToken());
		prog = new StringTokenizer (st.nextToken(), ";", false);
		post = new Condition (st.nextToken());
		program = new LinkedList<Statement>();
		while (prog.hasMoreTokens())
			program.add(new Statement (prog.nextToken()));
		
	}
	
	public static boolean testAll () {
		
		int [] vals, newVals;
		
		vals = new int [3];
		newVals = new int [3];
		for (vals[0]=0 ; vals[0]<=100 ; vals[0]++)
			for (vals[1]=0 ; vals[1]<=100 ; vals[1]++)
				for (vals[2]=0 ; vals[2]<=100 ; vals[2]++)
					if (pre.eval(vals)) {
						newVals[0] = vals[0];
						newVals[1] = vals[1];
						newVals[2] = vals[2];
						// Los errores de ejecucion son manejados desde run.
						for (Statement s : program) {
							if (!s.run(newVals))
								return false;
						}
						if (!post.eval(newVals))
							return false;
					}
		
		return true;
		
	}

	public static void main (String [] args) {
		
		Scanner S;
		String buffer, tmp;
		int T, toGo, i;
		
		S = new Scanner(System.in);
		T = S.nextInt();
		
		while (T-- > 0) {
			buffer = "";
			toGo = 2;
			while (toGo != 0) {
				tmp = S.next();
				i = tmp.indexOf('}');
				if (i!=-1)
					toGo--;
				if (tmp.substring(i+1).indexOf('}')!=-1)
					toGo--;
				buffer += tmp;
			}
			parse(buffer);
			System.out.println(testAll() ? "CORRECT" : "INCORRECT");
		}
		
	}

}

class Condition {

	public static final int
					  OP_LT = 0
					, OP_GT = 1
					, OP_LE = 2
					, OP_GE = 3
					, OP_EQ = 4
					, OP_NQ = 5
					, OP_AND = 6;
	
	LinkedList<Condition> subs;

	Expression a, b;
	
	boolean subconditions;
	
	int op;
	
	public Condition (String buffer) {
		
		StringTokenizer st;
		String atmp, tmp;
		
		st = new StringTokenizer (buffer, ",", false);
		tmp = st.nextToken();
		if (st.hasMoreTokens()) {
			subs = new LinkedList<Condition> ();
			subs.add(new Condition(tmp));
			while (st.hasMoreTokens())
				subs.add(new Condition(st.nextToken()));
			op = OP_AND;
			subconditions = true;
			return;
		}
		
		st = new StringTokenizer (buffer, "<>=!", true);
		atmp = st.nextToken();
		tmp = st.nextToken();
		subconditions = false;
		switch (tmp.charAt(0)) {
			case '<':
				a = new Expression (atmp);
				tmp = st.nextToken();
				if (tmp.equals("=")) {
					op = OP_LE;
					b = new Expression (st.nextToken());
				} else {
					op = OP_LT;
					b = new Expression (tmp);
				}
				break;
			case '>':
				a = new Expression (atmp);
				tmp = st.nextToken();
				if (tmp.equals("=")) {
					op = OP_GE;
					b = new Expression (st.nextToken());
				} else {
					op = OP_GT;
					b = new Expression (tmp);
				}
				break;
			case '=':
				a = new Expression (atmp);
				op = OP_EQ;
				b = new Expression (st.nextToken());
				break;
			case '!':
				a = new Expression (atmp);
				st.nextToken();
				op = OP_NQ;
				b = new Expression (st.nextToken());
				break;
		}
		
	}
	
	public boolean eval (int [] vals) {
		
		boolean all;
		int x, y;
		
		if (op == OP_AND) {
			all = true;
			for (Condition c : subs)
				all = all && c.eval(vals);
			return all;
		}
		
		x = a.eval(vals);
		y = b.eval(vals);
		if (x<0 || x>100 || y<0 || y>100)
			return false;
		
		switch (op) {
			case OP_LT:
				return x < y;
			case OP_GT:
				return x > y;
			case OP_LE:
				return x <= y;
			case OP_GE:
				return x >= y;
			case OP_EQ:
				return x == y;
			case OP_NQ:
				return x != y;
		}
		return false;
		
	}

}

class Expression {

	public static final int
					  OP_ADD = 0
					, OP_SUB = 1
					, OP_MUL = 2
					, OP_DIV = 3
					, OP_NOP = 4;

	Value a, b;
	
	int op;
	
	public Expression (String buffer) {
		
		StringTokenizer st;
		
		st = new StringTokenizer (buffer, "+-*/", true);
		a = new Value (st.nextToken());
		
		if (!st.hasMoreTokens()) {
			op = OP_NOP;
			return;
		}
		switch (st.nextToken().charAt(0)) {
			case '+':
				op = OP_ADD;
				break;
			case '-':
				op = OP_SUB;
				break;
			case '*':
				op = OP_MUL;
				break;
			case '/':
				op = OP_DIV;
				break;
		}
		b = new Value (st.nextToken());
		
	}
	
	public int eval (int [] vals) {
		
		switch (op) {
			case OP_ADD:
				return a.eval(vals) + b.eval(vals);
			case OP_SUB:
				return a.eval(vals) - b.eval(vals);
			case OP_MUL:
				return a.eval(vals) * b.eval(vals);
			case OP_DIV:
				return a.eval(vals) / b.eval(vals);
			case OP_NOP:
				return a.eval(vals);
		}
		return 0;
		
	}

}

class Value {

	public static final int
					  X = 0
					, Y = 1
					, Z = 2;
	
	boolean isVar;
	
	int var, val;
	
	public Value (String buffer) {
		
		switch (buffer.charAt(0)) {
			case 'x':
				isVar = true;
				var = X;
				break;
			case 'y':
				isVar = true;
				var = Y;
				break;
			case 'z':
				isVar = true;
				var = Z;
				break;
			default:
				isVar = false;
				val = Integer.parseInt(buffer);
				break;
		}
		
	}
	
	public int eval (int [] vals) {
		
		if (isVar)
			return vals[var];
		return val;
		
	}
	
}

class Statement {

	Value var;
	
	Expression assig;
	
	public Statement (String buffer) {
		
		StringTokenizer st;
		
		st = new StringTokenizer (buffer, ":=", false);
		var = new Value (st.nextToken());
		assig = new Expression (st.nextToken());
		
	}
	
	public boolean run (int [] vals) {
		
		vals[var.var] = assig.eval(vals);
		
		return (0<=vals[var.var] && vals[var.var]<=100);
		
	}

}