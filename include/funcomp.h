//
// Created by marcel on 6/13/19.
//

#ifndef CPPFUNCOMP_H
#define CPPFUNCOMP_H
#include <type_traits>
#include <result_type.h>

namespace cppfuncomp{

    struct HigherOrderFunction{};
    template<typename Predicate>
    auto repeatWhile(Predicate predicate)
    {
        return [predicate](auto callee){
            bool success = true;
            while(success)
            {
                success = predicate(callee());
            }
        };
    }

    template <typename Pred> struct repeatUntil : HigherOrderFunction
    {
        Pred m_pred;
        repeatUntil(Pred pred)
                : m_pred(pred)
        {
        }
        template <typename Callee> auto operator()(Callee&& callee) const
        {
            return [pred=m_pred, callee_=std::move(callee)](auto &&... args) {
                while (true)
                {
                    auto const result = callee_(args...);
                    if (pred(result))
                        return result;
                }
            };
        }
    };
    template<typename Callee>
    struct Do
    {
        Callee callee;
        constexpr Do(Callee callee_)
                    :callee(callee_)
                    {}
        template<typename Pred>
        constexpr auto If(Pred&& pred)
        {
            return [callee_=callee, pred](auto && value){
                if (pred(value))
                {
                    if constexpr (std::is_invocable_v<Callee,decltype(value)>)
                    {
                        return callee_(value);
                    }
                    else
                    {
                        return callee_();
                    }
                }
                return value;
            };
        }
    };

    template <typename Callee, typename Caller> auto operator|(Callee&& callee, Caller&& caller)
    {
        if constexpr (std::is_base_of_v<cppfuncomp::HigherOrderFunction, Caller>)
        {
            return [hof = std::forward<Caller>(caller)(std::forward<Callee>(callee))](auto&&... arg)
            {
                return hof(std::forward<decltype(arg)>(arg)...);
            };
        }
        else
        {
            return [callee_=std::move(callee), caller_=std::move(caller)](auto&&... arg) {
                if constexpr ((sizeof...(arg) == 1)&&( ... && ( ResultType::is_result_type<decltype(arg)>::value))){
                    return  ResultType::operator|(ResultType::operator|(std::forward<decltype(arg)>(arg)..., callee_), caller_);
                }
                else
                {
                    using CalleReturnType = decltype(callee_(std::forward<decltype(arg)>(arg)...));

                    if constexpr (std::is_invocable_v<Caller, CalleReturnType>)
                    {
                        return caller_(callee_(std::forward<decltype(arg)>(arg)...));
                    }
                    else if constexpr (ResultType::is_result_type<CalleReturnType>::value)
                    {
                        return ResultType::operator|(callee_(std::forward<decltype(arg)>(arg)...), caller_);
                    }
                }
            };
        }
    }

    }

#endif //CPPFUNCOMP_H
