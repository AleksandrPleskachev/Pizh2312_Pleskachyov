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