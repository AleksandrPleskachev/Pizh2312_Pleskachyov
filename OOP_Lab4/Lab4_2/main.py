# Программирование на языке высокого уровня (Python).
# Задание week_04_1. Вариант 7
#
# Выполнил: Плескачёв А.М
# Группа: ПИЖ-б-о-23-1(2)


from stack import Stack

def test_stack_operations():
    """Тестирование основных операций со стеком."""
    print("1. Создание стека")
    s = Stack([1, 2, 3])
    print(f"Стек: {s}")
    print(f"Размер стека: {s.size}")
    
    print("\n2. Добавление элементов")
    s.push(4)
    s.push(5)
    print(f"Стек после push(4), push(5): {s}")
    
    print("\n3. Удаление элементов")
    print(f"pop(): {s.pop()}")
    print(f"peek(): {s.peek()}")
    print(f"Стек после pop(): {s}")
    
    print("\n4. Проверка на пустоту")
    print(f"Стек пуст? {s.is_empty()}")
    s.clear()
    print(f"После clear(): {s}")
    print(f"Стек пуст? {s.is_empty()}")
    
    print("\n5. Создание стека из строки")
    s2 = Stack.from_string("a, b, c, d")
    print(f"Стек из строки: {s2}")
    
    print("\n6. Сохранение и загрузка из файла")
    s2.save("stack.json")
    s3 = Stack()
    s3.load("stack.json")
    print(f"Загруженный стек: {s3}")
    
    print("\n7. Объединение стеков")
    s4 = Stack([1, 2]) + Stack([3, 4])
    print(f"Объединенный стек: {s4}")
    
    print("\n8. Проверка наличия элемента")
    print(f"Элемент '3' в стеке? {'3' in s3}")
    print(f"Элемент 'x' в стеке? {'x' in s3}")

if __name__ == "__main__":
    test_stack_operations()