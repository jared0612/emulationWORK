#include<iostream>
#include<mutex>
#include<atomic>

/*
1、单例模式
2、工厂模式
*/

//设计模式：两种单例模式的设计方式

class Singleton {

private:
    Singleton(){}
    ~Singleton(){}

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static Singleton *m_instance;
    static std::mutex m_mutex;

public:
    static Singleton* GetInstance() {
        if (m_instance == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);//锁管理器；
            if (m_instance == nullptr) {
                m_instance = new Singleton();
                static Garhuishou gl;//创建局部的静态变量，直到程序结束会自己动释放；
            }
            
        }
        return m_instance;
    }
    class Garhuishou{
    public:
        ~Garhuishou() {
            if (m_instance != nullptr) {
                delete m_instance;
                m_instance = nullptr;
            }
        }
    };
};
Singleton* Singleton::m_instance = nullptr;
std::mutex Singleton::m_mutex;



class Singleton2
{
private:
    Singleton2() = default;
public:
    ~Singleton2() = default;

private:
    static std::atomic<Singleton2*> m_instance;  // 使用原子指针
    static std::mutex m_mutex;                 // 用于多线程同步

public:
    static Singleton2* GetInstance()
    {
        Singleton2* instance = m_instance.load(std::memory_order_acquire);  // 原子加载
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(m_mutex);  // 加锁
            instance = m_instance.load(std::memory_order_relaxed);  // 再次检查
            if (instance == nullptr)
            {
                instance = new Singleton2();  // 创建实例
                m_instance.store(instance, std::memory_order_release);  // 原子存储
            }
        }
        return instance;
    }
};

// 初始化静态成员
std::atomic<Singleton2*> Singleton2::m_instance{nullptr};
std::mutex Singleton2::m_mutex;

class Base {
public:
    virtual void produce() = 0;
    //virtual void consume();
    virtual ~Base(){}

};

class Factory1:public Base {
public:
    void produce()final{std::cout<<"Factory1\n";}
};

class Factory2:public Base {
public:
    void produce()final{std::cout<<"Factory2\n";}

};

void run(Base &base) {
    base.produce();
}

int main() {
    Singleton *newinstance = Singleton::GetInstance();
    Singleton2 *newinstance2 = Singleton2::GetInstance();

    Singleton *again = Singleton::GetInstance();
    Singleton2 *again2 = Singleton2::GetInstance();

    if (newinstance == again) std::cout << "same object.\n"; 
    if (newinstance2 == again2) std::cout << "same object2.\n"; 


    Base *base1 = new Factory1;

    run(*base1);

    Base *base2 = new Factory2;
    run(*base2);

    std::cin.get();

    return 0;
}