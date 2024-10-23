public class Converter {

    public static String convertToInfix(String prefix) {

        StringDoubleendedQueueImpl<String> queue = new StringDoubleendedQueueImpl<>();
        String[] tokens = new String[prefix.length()];

		for (int i = 0; i < prefix.length(); i++) {
		  char c = prefix.charAt(i);
		  String s = String.valueOf(c);
		  tokens[i] = s;
		}

            for (int i = tokens.length - 1; i >= 0; i--) {
                String token = tokens[i];
                if (isOperator(token)) {
                    if (queue.size() < 2) {
                        throw new IllegalArgumentException("Invalid expression: insufficient operands");
                    }
                    String operand1 = queue.removeFirst();
                    String operand2 = queue.removeFirst();
					if (isOperator1(token)){
						String infix = "(" + operand1 + token + operand2 + ")";
						queue.addFirst(infix);
					}else{
						String infix = operand1 + token + operand2;	
						queue.addFirst(infix);
					}
                } else {
                    queue.addFirst(token);
                }
            }
        
            if (queue.size() != 1) {
                throw new IllegalArgumentException("illegal operand");
            }
        
            return queue.getFirst();
    }

   

    private static boolean isOperator(String token) {
        return token.equals("+") || token.equals("-") || token.equals("*") || token.equals("/");
    }
	
	private static boolean isOperator1(String token) {
        return token.equals("+") || token.equals("-");
    }
}