from stack import Stack, test_stack_operations
from stack_collection import StackCollection

def test_stack_collection():
    """Тестирование класса StackCollection."""
    print("\n=== Тестирование коллекции стеков ===")
    print("1. Создание коллекции стеков")
    sc = StackCollection([Stack([1, 2]), Stack(['a', 'b'])])
    print(f"Коллекция: {sc}")
    
    print("\n2. Добавление и удаление стеков")
    sc.add(Stack([True, False]))
    print(f"После добавления: {sc}")
    removed = sc.remove(1)
    print(f"Удален стек: {removed}")
    print(f"После удаления: {sc}")
    
    print("\n3. Индексация и срезы")
    print(f"Первый стек: {sc[0]}")
    sc.add(Stack(['x', 'y', 'z']))
    sc.add(Stack([10, 20, 30]))
    print(f"Стеки 1-2: {sc[1:3]}")
    
    print("\n4. Сохранение и загрузка")
    sc.save("stack_collection.json")
    sc2 = StackCollection()
    sc2.load("stack_collection.json")
    print(f"Загруженная коллекция: {sc2}")
    
    print("\n5. Дополнительные методы")
    print(f"Общее количество элементов: {sc2.total_elements}")
    print(f"Стеки, содержащие 'x': {sc2.find_stacks_with_element('x')}")
    print(f"Объединенный стек: {sc2.merge_all_stacks()}")

if __name__ == "__main__":
    print("=== Тестирование стека ===")
    test_stack_operations()
    test_stack_collection()