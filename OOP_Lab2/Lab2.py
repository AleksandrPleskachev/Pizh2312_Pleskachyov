from abc import ABC, abstractmethod
from typing import List, Tuple


# Абстрактный базовый класс для робота (абстракция)
class AbstractRobot(ABC):
    @abstractmethod
    def move(self, direction: str) -> None:
        """Перемещает робота в указанном направлении."""
        pass

    @abstractmethod
    def path(self) -> List[Tuple[int, int]]:
        """Возвращает список координат, по которым двигался робот."""
        pass


# Класс для управления координатами (композиция)
class Position:
    def __init__(self, x: int, y: int):
        self.__x: int = max(0, min(x, 100))  # Инкапсуляция: приватные поля
        self.__y: int = max(0, min(y, 100))

    @property
    def x(self) -> int:
        """Геттер для координаты X."""
        return self.__x

    @property
    def y(self) -> int:
        """Геттер для координаты Y."""
        return self.__y

    def update(self, dx: int, dy: int) -> None:
        """Обновляет координаты с учётом ограничений (0-100)."""
        new_x = max(0, min(self.__x + dx, 100))
        new_y = max(0, min(self.__y + dy, 100))
        self.__x = new_x
        self.__y = new_y


# Основной класс Robot (наследование от AbstractRobot)
class Robot(AbstractRobot):
    def __init__(self, x: int = 0, y: int = 0) -> None:
        """
        Инициализирует робота с начальными координатами.

        Args:
            x (int): Начальная координата X (0-100).
            y (int): Начальная координата Y (0-100).
        """
        self._position: Position = Position(x, y)  # Композиция
        self._path: List[Tuple[int, int]] = [(self._position.x, self._position.y)]  # Инкапсуляция

    def move(self, direction: str) -> None:
        """
        Перемещает робота на одну клетку в указанном направлении.

            direction (str): Направление движения (N, S, E, W).

            ValueError: Если направление не является одним из допустимых (N, S, E, W).
        """
        # Проверка направления в рантайме
        valid_directions = {"N", "S", "E", "W"}
        if direction not in valid_directions:
            raise ValueError(f"Недопустимое направление: {direction}. Допустимые направления: {valid_directions}")

        dx, dy = 0, 0
        if direction == "N":
            dy = 1
        elif direction == "S":
            dy = -1
        elif direction == "E":
            dx = 1
        elif direction == "W":
            dx = -1

        self._position.update(dx, dy)
        self._path.append((self._position.x, self._position.y))

    def path(self) -> List[Tuple[int, int]]:
        """
        Возвращает список координат, по которым двигался робот.

        Returns:
            List[Tuple[int, int]]: Список координат (x, y).
        """
        return self._path

    def __call__(self, direction: str) -> None:
        """
        Вызывает метод move при вызове объекта как функции.

            direction (str): Направление движения (N, S, E, W).

            ValueError: Если направление не является одним из допустимых (N, S, E, W).
        """
        self.move(direction)


# Класс-наследник с изменённым поведением (полиморфизм)
class FastRobot(Robot):
    def move(self, direction: str) -> None:
        """
        Перемещает робота на две клетки вместо одной (полиморфизм).

            direction (str): Направление движения (N, S, E, W).

            ValueError: направление не является одним из допустимых (N, S, E, W).
        """
        # Проверка направления в рантайме
        valid_directions = {"N", "S", "E", "W"}
        if direction not in valid_directions:
            raise ValueError(f"Недопустимое направление: {direction}. Допустимые направления: {valid_directions}")

        dx, dy = 0, 0
        if direction == "N":
            dy = 2
        elif direction == "S":
            dy = -2
        elif direction == "E":
            dx = 2
        elif direction == "W":
            dx = -2

        self._position.update(dx, dy)
        self._path.append((self._position.x, self._position.y))


# Пример использования
if __name__ == "__main__":
    # Создаём обычного робота
    robot = Robot(50, 50)
    robot.move("N")  # Движение через метод
    robot("E")       # Движение через __call__
    robot.move("S")
    print("Путь обычного робота:", robot.path())

    # Создаём быстрого робота
    fast_robot = FastRobot(50, 50)
    fast_robot.move("N")  # Движение на 2 клетки
    fast_robot("W")
    print("Путь быстрого робота:", fast_robot.path())
