# Python3 Note
## list
list是一种有序的集合，可以随时添加删除其中元素
> classmates = ['Michael', 'Bob', 'Tracy']

## tuple
tuple与list类似，但是tuple一旦初始化就不能修改
> classmates = ('Michael', 'Bob', 'Tracy')

## dict
1. dict内部存放的顺序和key放入的顺序是没有关系的；
2. 查找和插入的速度极快，不会随着key的增加而变慢；
3. 需要占用大量的内存，内存浪费多；

> score = {'Michael': 95, 'Bob': 75, 'Tracy': 85}

## set
set和dict类似，也是一组key的集合，但不存储value

> classmates = set(['Michael', 'Bob', 'Tracy'])

## function
https://docs.python.org/3/library/functions.html

> 1. *args是可变参数，args接收的是一个 tuple
> 2. **kw是关键字参数，kw接收的是一个 dict

## feature
### 切片
**L[x:y:z]**

* x: 起始索引值，缺省值为0
* y: 结束索引值(y-1)，缺省值为包含最后一个元素
* z: 每z个元素取一个值

### 迭代器 iterator
1. 凡是可作用于for循环的对象都是Iterable类型；
2. 凡是可作用于next()函数的对象都是Iterator类型，它们表示一个惰性计算的序列；
3. 集合数据类型如list、dict、str等是Iterable但不是Iterator，不过可以通过iter()函数获得一个Iterator对象。

## functional programming
既然变量可以指向函数，函数的参数能接收变量，那么一个函数就可以接收另一个函数作为参数，这种函数就称之为高阶函数

### map & reduce
* map(func, args) = (func(arg1), func(arg2), func(arg3))
* reduce(func, args) = func(func(arg1, arg2), arg3)

返回一个函数时，牢记该函数并未执行，返回函数中不要引用任何可能会变化的变量

## module
__init__.py可以是空文件，也可以有Python代码，因为__init__.py本身就是一个模块，而它的模块名就是所在包名

## OOP
### Object Oriented Programming
数据封装、继承和多态是面向对象的三大特点

* data packaging

* restricting access
> 1. 果要让内部属性不被外部访问，可以把属性的名称前加上两个下划线__，在Python中，实例的变量名如果以__开头，就变成了一个私有变量（private），只有内部可以访问，外部不能访问
> 2. 需要注意的是，在Python中，变量名类似__xxx__的，也就是以双下划线开头，并且以双下划线结尾的，是特殊变量，特殊变量是可以直接访问的，不是private变量
> 3. 以一个下划线开头的实例变量名，比如_name，这样的实例变量外部是可以访问的，但是，按照约定俗成的规定，当你看到这样的变量时，意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问”

* inherit

### 实例属性 & 类属性
不要把实例属性和类属性使用相同的名字，因为相同名称的实例属性将屏蔽掉类属性，但是当你删除实例属性后，再使用相同的名称，访问到的将是类属性。
