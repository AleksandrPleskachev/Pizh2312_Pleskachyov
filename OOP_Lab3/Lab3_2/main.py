from roman import Roman


def main():
    # Пример использования класса Roman
    try:
        num1 = Roman('X')  # 10
        num2 = Roman('V')   # 5

        print(f"{num1} + {num2} = {num1 + num2}")  # X + V = XV
        print(f"{num1} - {num2} = {num1 - num2}")  # X - V = V
        print(f"{num1} * {num2} = {num1 * num2}")  # X * V = L
        print(f"{num1} / {num2} = {num1 / num2}")  # X / V = II

    except Exception as e:
        print(f"Ошибка: {e}")


if __name__ == "__main__":
    main()