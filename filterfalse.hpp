#pragma once
#include <iterator>

namespace itertools{
    template<class IF,class C> class filterfalse {

    protected:
        
        const C& container;
        const IF& condition;
    public:
       
        filterfalse( const IF& cond,const C& cont ):container(cont),condition(cond){}

        
        class iterator {

        private:
            
            const filterfalse& ff;
            decltype(container.begin()) iter;

        public:
            //Constructor
            iterator(const filterfalse& ffT,decltype(container.begin()) iterT )
                    :ff(ffT),iter(iterT)
            {
                
                while(iter!=ff.container.end() && ff.condition(*iter)) iter++;
            }

            auto operator*() const {
                return *iter;
            }

            //++iter
            iterator& operator++() {
                ++iter;
                
                while(iter!=ff.container.end() && ff.condition(*iter))++iter ;
                return *this;
            }

            //iter++
            const iterator operator++(int) {
                iterator tmp= *this;
                ++iter;
                return tmp;
            }

            bool operator==(const iterator& iterator) const {
                return iterator.iter==iter;
            }

            bool operator!=(const iterator& iterator) const {
                return iterator.iter!=iter;
            }
        }; 


        iterator begin() const {
            return iterator(*this,container.begin());
        }

        iterator end() const {
            return iterator(*this,container.end());
        }
    };

}
