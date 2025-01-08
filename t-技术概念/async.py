# 今天使用下python的异步编程，
# 异步编程可以在IO密集型的工作上发挥作用，并发的执行任务
# 异步编程可以使用asyncio库， asyncio是python的异步I/O和并发编程标准库
# asyncio库提供了一个事件循环，事件循环可以让我们在后台执行任务， 
# 通过在函数名前使用async关键字来表示该函数是一个异步函数，
# 使用asyncio.create_task()来创建并发任务，将协程包装成任务对象；
# 使用await关键字来等待异步函数的返回值
# 使用awit asyncio.gather()来等待任务完成；
# asyncio.run来执行事件循环；
# 异步编程主要依赖以下概念：
# 1、async和await：创建和等待协程；
# 2、asyncio模块：提供事件循环、任务调度；
# 3、task对象：待执行的工作单元
# 4、异步上下文管理使用async with as 语法
# 5、with xx as xx简化资源管理的过程，上下文管理对象必须实现__enter__\__exit__方法
# 6、as后的变量通常赋值为__enter__方法的返回值；
# 7、with前执行__enter__方法，with块后执行__exit__方法


import asyncio

async def greet(name):
    print(f"Hello,{name}")
    await asyncio.sleep(2)
    print(f"Goodbye,{name}")

async def main():

    task1 = asyncio.create_task(greet("码农"))
    task2 = asyncio.create_task(greet("研究僧"))
    #await greet("码农")
    #await greet("研究僧")
    await asyncio.gather(task1, task2)

if __name__ == "__main__":
    asyncio.run(main())
