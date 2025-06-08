In mathematics, a Square is a Rectangle. Indeed it is a specialization of a rectangle. The "IS A" makes 
you want to model this with inheritance. However if in code you made Square derive from Rectangle, then 
a Square should be usable anywhere you expect a Rectangle. This makes for some strange behaviour as follows:

#include <iostream>
#include <cstdint>
#include <cassert>

struct Rectangle {
    Rectangle(const uint32_t width, const uint32_t height) : m_width{width}, m_height{height} {}

    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }

    virtual void set_width(const uint32_t width) { this->m_width = width; }
    virtual void set_height(const uint32_t height) { this->m_height = height; }

    uint32_t area() const { return m_width * m_height; }

protected:
    uint32_t m_width, m_height;
};

struct Square : Rectangle {
    Square(uint32_t size) : Rectangle(size, size) {}
    void set_width(const uint32_t width) override { this->m_width = m_height = width; }
    void set_height(const uint32_t height) override { this->m_height = m_width = height; }
};

void process(Rectangle &r) {
    uint32_t w = r.get_width();
    r.set_height(10);

    assert((w * 10) == r.area()); // Fails for Square <--------------------
}

int main() {
    Rectangle r{5, 5};
    process(r);
    Square s{5};
    process(s);
    return EXIT_SUCCESS;
}

 - As you can see above, we have violated Liskovs's Substitution Principle in the void process(Rectangle &r) function. 
   Therefore Square is not a valid substitute of Rectangle.
 - If you see from the design perspective, the very idea of inheriting Square from Rectangle is not a good idea. 
  Because Square does not have height & width, rather it has the size/length of sides.



Using proper inheritance hierarchy:

struct Shape {
    virtual uint32_t area() const = 0;
};

struct Rectangle : Shape {
    Rectangle(const uint32_t width, const uint32_t height) : m_width{width}, m_height{height} {}

    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }

    virtual void set_width(const uint32_t width) { this->m_width = width; }
    virtual void set_height(const uint32_t height) { this->m_height = height; }

    uint32_t area() const override { return m_width * m_height; }

private:
    uint32_t m_width, m_height;
};

struct Square : Shape {
    Square(uint32_t size) : m_size(size) {}
    void set_size(const uint32_t size) { this->m_size = size; }
    uint32_t area() const override { return m_size * m_size; }

private:
    uint32_t m_size;
};

void process(Shape& s) {
    // This function only knows about the 'Shape' interface.
    // It can reliably call 'area()' because both Rectangle and Square
    // correctly implement this part of the Shape contract.
    std::cout << "Shape area: " << s.area() << std::endl;

    // IMPORTANT: 'process' CANNOT do this now, and that's GOOD for LSP:
    // s.set_width(10);  // COMPILE ERROR: 'Shape' has no member 'set_width'
    // s.set_height(10); // COMPILE ERROR: 'Shape' has no member 'set_height'
    // This prevents the previous LSP violation because the client (process)
    // is restricted to using only the common, safely substitutable interface.
}
int main() {
    Rectangle my_rectangle(5, 10);
    Square my_square(7);

    // Using the 'process' function, which expects a 'Shape' reference.
    // Both 'my_rectangle' and 'my_square' can be substituted for 'Shape'
    // without breaking the 'process' function's expectations regarding 'area()'.
    process(my_rectangle); // Output: Shape area: 50
    process(my_square);    // Output: Shape area: 49

    // Specific operations on concrete types (not related to LSP through 'process')
    my_rectangle.set_width(6);
    // std::cout << "Rectangle area after set_width: " << my_rectangle.area() << std::endl; // For verification: 60

    my_square.set_size(8);
    // std::cout << "Square area after set_size: " << my_square.area() << std::endl; // For verification: 64

    return 0;
}

Benefits of Liskov's Substitution Principle
=> Compatibility
It enables the binary compatibility between multiple releases & patches. In other words, It keeps the client code away from being impacted.
=> Type Safety
It's the easiest approach to handle type safety with inheritance, as types are not allowed to vary when inheriting.
=> Maintainability
Code that adheres to LSP is loosely dependent on each other & encourages code reusability.
Code that adheres to the LSP is code that makes the right abstractions.
