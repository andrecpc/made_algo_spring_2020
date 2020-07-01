from pyparsing import *

ParserElement.enablePackrat()

number = pyparsing_common.number
variable = OneOrMore(Word(alphas))
operand = number | variable

expop = Literal('^')
multop = oneOf('* /')
plusop = oneOf('+ -')

expr = variable + '=' + infixNotation(
    operand,
    [(expop, 2, opAssoc.RIGHT),
     (multop, 2, opAssoc.LEFT),
     (plusop, 2, opAssoc.LEFT),]
)

def acc(a, op, b):
    if op == '+':
        return a + b
    elif op == '-':
        return a - b
    elif op == '*':
        return a * b
    elif op == '/':
        if b == 0:
            raise ZeroDivisionError("Деление на ноль")
        return a / b
    elif op == '^':
        return a ** b

def transform(line):
    if type(line)==int:
        return line

    if type(line)==float:
        return line

    if type(line) == str:
        if line not in variables:
            raise BaseException("Переменная  {} неопределена".format(line))
        return variables[line]

    out = transform(line[0])
    i = 1
    while i < len(line):
        op = line[i]
        i += 1
        val = transform(line[i])
        i += 1
        out = acc(out, op, val)
    return out

if __name__ == "__main__":

    variables = {}

    with open("std.in", "r") as file:
        for i, line in enumerate(file):

            try:
                var, equal, statement = expr.parseString(line, parseAll=True)
                variables[var] = transform(statement)
                print(var, '=', variables[var])

            except BaseException as e:
                print(e)
