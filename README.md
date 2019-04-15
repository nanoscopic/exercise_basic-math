# exercise_basic-math

## Basic Math
Write a basic math library capable of handling simple expressions.

Stages:

 1. Addition / Subtraction
	 Make code capable of parsing expressions consisting of numbers and + or - operators. 
 2. Parentheses
	 Additionally handle arbitrary grouping by parentheses. They can be nested an arbitrary number of levels deep.
 3. Multiplication / Division
	 Make the system capable of handling multiplication and division also. For ease execute immediately in sequence rather than using precedence rules.
 4. Precedence
	 Follow proper precedence rules of basic algebra ( do multiplication/division before addition/subtraction )

### Approaches for 1: Add/Sub

1. Build numbers till you hit an operator; once you hit an operator execute the last operation. Also execute when the end of the string is reached. This works as a single pass.
2. Tokenize numbers and operators into a linked list. This has the added benefit of being flexible for future changes.

### Approaches for 2: Parentheses

1. Recurse into parsing whenever a paran is seen. Exit recursion when encountering a ending paran.
2. Ignore +() as it effectively changes nothing. Only handle -() and do so by inverting all add/sub operators within the parans. This has the benefit of being able to do everything in a single pass.
3. Tokenize expressions into more complex objects. ( a "paran" group of a series of operations )

### Approaches for 3: Mult/Divide

1. Recursion to evaluate groups.
2. Tokenization to evaluate groups.

### Approaches for 4: Precedence

1. A single pass approach is not longer possible. A preparse method is doable.
2. Tokenization with order setting of operations

### Overall approach:
Overall tokenization of the input seems to be the most flexible approach to handle all stages. Will therefore follow this approach rather than attempt to do initial stages in a single pass.




