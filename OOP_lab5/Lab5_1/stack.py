import json
from typing import Any, List, Optional

class Stack:
    """
    Класс, реализующий структуру данных Stack (стек) с основными операциями.
    Стек работает по принципу LIFO (Last In - First Out).
    """
    
    def __init__(self, elements: Optional[List[Any]] = None) -> None:
        """
        Инициализация стека.
        
        Args:
            elements: Начальные элементы стека (по умолчанию None - пустой стек)
        """
        self.__data = elements.copy() if elements else []
    
    def __str__(self) -> str:
        """
        Строковое представление стека.
        
        Returns:
            str: Строка с элементами стека
        """
        return f"Stack({self.__data})"
    
    def __len__(self) -> int:
        """
        Возвращает количество элементов в стеке.
        
        Returns:
            int: Количество элементов
        """
        return len(self.__data)
    
    def __eq__(self, other: 'Stack') -> bool:
        """
        Проверка на равенство двух стеков.
        
        Args:
            other: Другой стек для сравнения
            
        Returns:
            bool: True если стеки равны, иначе False
        """
        if not isinstance(other, Stack):
            return False
        return self.__data == other._Stack__data
    
    def push(self, item: Any) -> None:
        """
        Добавляет элемент в вершину стека.
        
        Args:
            item: Элемент для добавления
        """
        self.__data.append(item)
    
    def pop(self) -> Any:
        """
        Удаляет и возвращает элемент из вершины стека.
        
        Returns:
            Any: Элемент из вершины стека
            
        Raises:
            IndexError: Если стек пуст
        """
        if not self.__data:
            raise IndexError("Pop from empty stack")
        return self.__data.pop()
    
    def peek(self) -> Any:
        """
        Возвращает элемент из вершины стека без его удаления.
        
        Returns:
            Any: Элемент из вершины стека
            
        Raises:
            IndexError: Если стек пуст
        """
        if not self.__data:
            raise IndexError("Peek from empty stack")
        return self.__data[-1]
    
    def is_empty(self) -> bool:
        """
        Проверяет, пуст ли стек.
        
        Returns:
            bool: True если стек пуст, иначе False
        """
        return len(self.__data) == 0
    
    def clear(self) -> None:
        """
        Очищает стек, удаляя все элементы.
        """
        self.__data.clear()
    
    @property
    def size(self) -> int:
        """
        Возвращает количество элементов в стеке (свойство).
        
        Returns:
            int: Количество элементов
        """
        return len(self.__data)
    
    @classmethod
    def from_string(cls, str_value: str) -> 'Stack':
        """
        Создает стек из строкового представления.
        
        Args:
            str_value: Строка с элементами стека (формат: "1,2,3")
            
        Returns:
            Stack: Новый стек с элементами из строки
        """
        elements = [item.strip() for item in str_value.split(',')]
        return cls(elements)
    
    def save(self, filename: str) -> None:
        """
        Сохраняет стек в JSON файл.
        
        Args:
            filename: Имя файла для сохранения
        """
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump(self.__data, f)
    
    def load(self, filename: str) -> None:
        """
        Загружает стек из JSON файла.
        
        Args:
            filename: Имя файла для загрузки
        """
        with open(filename, 'r', encoding='utf-8') as f:
            self.__data = json.load(f)
    
    def __add__(self, other: 'Stack') -> 'Stack':
        """
        Объединяет два стека (конкатенация).
        
        Args:
            other: Другой стек для объединения
            
        Returns:
            Stack: Новый стек с элементами обоих стеков
        """
        return Stack(self.__data + other._Stack__data)
    
    def __contains__(self, item: Any) -> bool:
        """
        Проверяет, содержится ли элемент в стеке.
        
        Args:
            item: Элемент для поиска
            
        Returns:
            bool: True если элемент найден, иначе False
        """
        return item in self.__data


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