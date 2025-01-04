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
