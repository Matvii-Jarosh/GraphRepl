# Math

## `+` `-` `*` `/`  
Прості арифметичні операції для додавання, віднімання, множення та ділення.  

**Приклад:**

```lisp
(+ 1 2)
(- 10 5)
(* 3 4)
(/ 20 5)
```

## `sqrt`
Функція обчислює квадратний корінь з числа.

**Приклад:**

```lisp
(sqrt 16)
```

## `pow`
Функція підносить число до заданого степеня. Приймає два аргументи: базу та степінь.

**Приклад:**

```lisp
(pow 2 3)
```

## `sqrt` `pow` `sin` `cos` `tan` `asin` `acos` `atan`
Математичні функції для обчислень, включаючи корінь, степінь та тригонометрію.

- `sqrt` — квадратний корінь числа.
- `pow` — піднесення числа до степеня.
- `sin` — синус кута (в радіанах).
- `cos` — косинус кута (в радіанах).
- `tan` — тангенс кута (в радіанах).
- `asin` — арксинус значення, повертає кут в радіанах.
- `acos` — арккосинус значення, повертає кут в радіанах.
- `atan` — арктангенс значення, повертає кут в радіанах.

**Приклад:**

```lisp
(sqrt 16)  
(pow 2 3)  
(sin (/ 3.14 2))  
(cos 0)  
(tan (/ 3.14 4))  
(asin 1)  
(acos 1)  
(atan 1)
```

## `draw-plot`
Створює нове окно з графіком функції. Примає ширину, висоту на lambda функцію з 1 аргументом

**Приклад:**

```lisp
(draw-plot 100 100 (lambda (x) (sin x)))
```
