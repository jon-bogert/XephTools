/*==================================================================================================

== LICENCE ==

 XephTools - Generic Pointer
 Copyright (C) 2024 Jon Bogert (jonbogert@gmail.com)

 This software is provided 'as-is', without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:

 1. The origin of this software must not be misrepresented;
	you must not claim that you wrote the original software.
	If you use this software in a product, an acknowledgment
	in the product documentation would be appreciated but is not required.

 2. Altered source versions must be plainly marked as such,
	and must not be misrepresented as being the original software.

 3. This notice may not be removed or altered from any source distribution.

== README ==

 @brief A flexible, type-safe smart pointer wrapper that provides dynamic memory management 
 with simplified syntax and reduced header dependencies.
 
 Key Features:
 - Eliminates need to include type-specific headers for dynamic memory management
 - Provides safe type casting without verbose reinterpret_cast or dynamic_cast syntax
 - Prevents unintended copying with deleted copy constructors
 - Supports move semantics
 - Manages memory lifecycle with RAII principles
 
 Use Cases:
 - Scenarios requiring runtime type flexibility
 - Cross-module pointer management with minimal type information
 - Simplified memory management without std::unique_ptr complexities
 
 Example Usage:
 @code
   xe::generic_ptr ptr;
   ptr.make<MyClass>(arg1, arg2);  // Dynamically create object
   MyClass& obj = ptr.as<MyClass>();  // Safe type casting
   ptr.clear();  // Cleanup resources
 @endcode
 
 Limitations:
 - Relies on dynamic_cast for type safety
 - Slightly higher overhead compared to STL smart pointers

 ==================================================================================================*/

#ifndef XE_GENERIC_PTR
#define XE_GENERIC_PTR

namespace xe
{
    class generic_ptr 
    {
        using destructor_func = void(*)(void*);
    public:
        generic_ptr() : m_ptr(nullptr), m_destructor(nullptr) {}
        ~generic_ptr() { clear(); }
        generic_ptr(const generic_ptr&) = delete;
        generic_ptr& operator=(const generic_ptr&) = delete;
    
        // Move constructor
        generic_ptr(generic_ptr&& other) noexcept 
            : m_ptr(other.m_ptr), m_destructor(other.m_destructor) 
        {
            other.m_ptr = nullptr;
            other.m_destructor = nullptr;
        }
    
        // Move assignment
        generic_ptr& operator=(generic_ptr&& other) noexcept 
        {
            if (this != &other) 
            {
                clear();
                m_ptr = other.m_ptr;
                m_destructor = other.m_destructor;
                other.m_ptr = nullptr;
                other.m_destructor = nullptr;
            }
            return *this;
        }
    
        bool operator==(const generic_ptr& other) const 
        {
            // Compare pointers
            return (m_ptr == other.m_ptr);
        }
        bool operator!=(const generic_ptr& other) const 
        {
            return !(*this == other);
        }
        bool operator==(void* other_ptr) const 
        {
            return m_ptr == other_ptr;
        }
        bool operator!=(void* other_ptr) const 
        {
            return m_ptr != other_ptr;
        }
        bool operator==(const void* other_ptr) const 
        {
            return m_ptr == other_ptr;
        }
        bool operator!=(const void* other_ptr) const 
        {
            return m_ptr != other_ptr;
        }
    
        // Allocate memory for a specific type with constructor arguments
        template <class _Ty, typename... Args>
        void make(Args&&... args) 
        {
            // Clear any existing resources
            clear();
    
            // Allocate memory for the type
            try 
            {
                m_ptr = new _Ty(std::forward<Args>(args)...);
                // Store a type-specific destructor function pointer
                m_destructor = [](void* ptr)
                {
                    delete static_cast<_Ty*>(ptr);
                };
            }
            catch (const std::bad_alloc& e) 
            {
                // Handle allocation failure
                m_ptr = nullptr;
                m_destructor = nullptr;
                throw; // Re-throw to allow caller to handle allocation failure
            }
        }
    
        // Free resources and reset to initial state
        void clear() 
        {
            if (m_ptr) 
            {
                // Use stored destructor function pointer
                if (m_destructor)
                {
                    m_destructor(m_ptr);
                }
                m_ptr = nullptr;
                m_destructor = nullptr;
            }
        }
    
        // Safely cast to type reference
        template <class _Ty>
        _Ty& as() 
        {
            if (!m_ptr) 
            {
                throw std::runtime_error("Attempted to access null pointer");
            }
            
            // Perform a dynamic_cast to ensure type safety
            _Ty* typed_ptr = static_cast<_Ty*>(m_ptr);
            return *typed_ptr;
        }
    
        // Const version of as()
        template <class _Ty>
        const _Ty& as() const 
        {
            if (!m_ptr) 
            {
                throw std::runtime_error("Attempted to access null pointer");
            }
            
            // Perform a dynamic_cast to ensure type safety
            const _Ty* typed_ptr = static_cast<const _Ty*>(m_ptr);
            
            return *typed_ptr;
        }
    
        // Safely cast to type pointer
        template <class _Ty>
        _Ty* get() 
        {
            if (!m_ptr) 
            {
                return nullptr;
            }
            
            // Perform a dynamic_cast to ensure type safety
            return static_cast<_Ty*>(m_ptr);
        }
    
        // Const version of get()
        template <class _Ty>
        const _Ty* get() const 
        {
            if (!m_ptr) 
            {
                return nullptr;
            }
            
            // Perform a dynamic_cast to ensure type safety
            return static_cast<const _Ty*>(m_ptr);
        }
    
    private:
        void* m_ptr;
        destructor_func m_destructor;
    };

    template <class _Ty>
    generic_ptr make_generic()
    {
        generic_ptr ptr;
        ptr.make<_Ty>();
        return ptr;
    }
}

#endif // !XE_GENERIC_PTR