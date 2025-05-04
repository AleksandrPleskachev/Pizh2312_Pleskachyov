import json
from typing import Any, List, Optional, Union
from stack import Stack

class StackCollection:
    """
    Класс-контейнер для хранения и управления набором объектов Stack.
    """
    
    def __init__(self, stacks: Optional[List[Stack]] = None) -> None:
        """
        Инициализация коллекции стеков.
        
        Args:
            stacks: Начальный список стеков (по умолчанию None - пустая коллекция)
        """
        self._data: List[Stack] = stacks.copy() if stacks else []
    
    def __str__(self) -> str:
        """
        Строковое представление коллекции.
        
        Returns:
            str: Строка с описанием всех стеков в коллекции
        """
        return f"StackCollection({len(self._data)} stacks: {[str(stack) for stack in self._data]})"
    
    def __len__(self) -> int:
        """
        Возвращает количество стеков в коллекции.
        
        Returns:
            int: Количество стеков
        """
        return len(self._data)
    
    def __getitem__(self, index: Union[int, slice]) -> Union[Stack, List[Stack]]:
        """
        Поддержка индексации и срезов для коллекции.
        
        Args:
            index: Индекс или срез
            
        Returns:
            Stack или List[Stack]: Стек или список стеков по индексу/срезу
            
        Raises:
            TypeError: Если индекс не int или slice
            IndexError: Если индекс вне диапазона
        """
        if isinstance(index, (int, slice)):
            return self._data[index]
        raise TypeError("Индекс должен быть целым числом или срезом")
    
    def add(self, stack: Stack) -> None:
        """
        Добавляет стек в коллекцию.
        
        Args:
            stack: Стек для добавления
        """
        if not isinstance(stack, Stack):
            raise TypeError("Можно добавлять только объекты класса Stack")
        self._data.append(stack)
    
    def remove(self, index: int) -> Stack:
        """
        Удаляет и возвращает стек из коллекции по индексу.
        
        Args:
            index: Индекс удаляемого стека
            
        Returns:
            Stack: Удаленный стек
            
        Raises:
            IndexError: Если индекс вне диапазона
        """
        if index < 0 or index >= len(self._data):
            raise IndexError("Индекс вне диапазона")
        return self._data.pop(index)
    
    def save(self, filename: str) -> None:
        """
        Сохраняет коллекцию стеков в JSON файл.
        
        Args:
            filename: Имя файла для сохранения
        """
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump([stack._Stack__data for stack in self._data], f)
    
    def load(self, filename: str) -> None:
        """
        Загружает коллекцию стеков из JSON файла.
        
        Args:
            filename: Имя файла для загрузки
        """
        with open(filename, 'r', encoding='utf-8') as f:
            data = json.load(f)
        self._data = [Stack(stack_data) for stack_data in data]
    
    @property
    def total_elements(self) -> int:
        """
        Возвращает общее количество элементов во всех стеках коллекции.
        
        Returns:
            int: Суммарное количество элементов
        """
        return sum(len(stack) for stack in self._data)
    
    def find_stacks_with_element(self, element: Any) -> List[Stack]:
        """
        Находит все стеки, содержащие указанный элемент.
        
        Args:
            element: Элемент для поиска
            
        Returns:
            List[Stack]: Список стеков, содержащих элемент
        """
        return [stack for stack in self._data if element in stack]
    
    def merge_all_stacks(self) -> Stack:
        """
        Объединяет все стеки коллекции в один стек.
        
        Returns:
            Stack: Новый стек, содержащий все элементы коллекции
        """
        result = Stack()
        for stack in self._data:
            result += stack
        return result