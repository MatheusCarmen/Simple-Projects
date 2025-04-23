number1 = 0
number2 = 0
result = 0
operation = ''

while True:
    try:
        number1 = int(input("Type the first number: "))
        while True:
            operation = input("Type the desired operation (+, -, *, /) or "
                              "'q' to quit: ").casefold()
            if operation in ['+', '-', '*', '/', 'q']:
                break
            else:
                print("Invalid operation! Please enter a valid operation.")

        if operation == 'q':
            print("Exiting the calculator. Goodbye!")
            break

        number2 = int(input("Type the second number: "))

        if operation == '+':
            result = number1 + number2
        elif operation == '-':
            result = number1 - number2
        elif operation == '*':
            result = number1 * number2
        elif operation == '/':
            if number2 != 0:
                result = number1 / number2
            else:
                result = "Error! Division by zero."

        print(str(number1) + " " + str(operation) + " " + str(number2) +
              " = " + str(result))

    except ValueError:
        print("Invalid input! Please enter numeric values.")
