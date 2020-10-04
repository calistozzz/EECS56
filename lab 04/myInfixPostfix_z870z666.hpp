#include "myStack_z870z666.hpp"
#include <typeinfo>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

class myInfixPostfix
{
    private:
        myStack<char> m_stack;
        myStack<float> calc_float;
        myStack<char> count;
        std::string thePostfix;
        std::string theone;



    public:
        myInfixPostfix(){

        }

        ~myInfixPostfix(){

        }

        std::string getPostfix(std::string str){

               signed int size = str.length();


               for(int i=0; i<size; i++){
                string nums;
                //cout<<str.at(i)<<endl;
                if(str.at(i) == ' '){

                }
                else if(isdigit(str.at(i))){
                     thePostfix = thePostfix + '(';

                    if(i == str.length()-1){
                        thePostfix = thePostfix + str.at(i);
                    }
                    else if(str.at(i+1) != ' '){
                        int j=1;
                        nums = str.at(i);
                        while(str.at(i+j) != ' '){
                            nums = nums+str.at(i+j);
                            j++;
                        }
                        thePostfix = thePostfix +nums;
                        i = i+j;
                    }
                    else{
                         thePostfix = thePostfix + str.at(i);
                        }


                     thePostfix = thePostfix + ')';
                }
                else if((m_stack.empty() || m_stack.top() == '(') && (str.at(i)== '+' || str.at(i) == '-' || str.at(i) == '*' || str.at(i) == '/')){

                    m_stack.push(str.at(i));
                }
                else if(str.at(i)== '+' || str.at(i) == '-' ){
                    // cout<<str.at(i)<<endl;
                    // cout<<i<<endl;
                    if(m_stack.top() == '+' || m_stack.top() =='-'){      // + or - at top of stack when comes + or -

                        thePostfix = thePostfix + m_stack.pop();
                        m_stack.push(str.at(i));
                    }
                    else if(m_stack.top() == '*' || m_stack.top() =='/'){   // * or / at top of stack when comes + or -

                       while(!m_stack.empty() ){
                           if(m_stack.top() == '('){
                            //    m_stack.push(str.at(i));
                               break;
                           }
                           else
                           {
                            thePostfix =  thePostfix +m_stack.pop();
                           }
                       }
                       m_stack.push(str.at(i));
                    }
                }
                else if(str.at(i) == '*' || str.at(i) == '/' ){      // * or / at otp of stack when comes * or /
                 //cout<<"niupi\n";
                    if(m_stack.top() == '*' || m_stack.top() =='/'){
                        thePostfix = thePostfix + m_stack.pop();
                        m_stack.push(str.at(i));
                    }
                    else if(m_stack.top() == '+' || m_stack.top() =='-'){       // + or - at top of stack when comes * or /
                        m_stack.push(str.at(i));
                    }
                }
                else if(str.at(i) == '('){
                    //cout<<"tai niu le\n";
                    m_stack.push(str.at(i));
                }
                else if(str.at(i) == ')'){
                    //cout<<"niudafale\n";
                    while(m_stack.top() != '('){
                        thePostfix = thePostfix + m_stack.pop();
                    }
                    m_stack.pop();
                }


                // cout<<thePostfix<<endl;

            }


             while(!m_stack.empty())
            {
                //cout<<m_stack.top()<<endl;
                thePostfix = thePostfix + m_stack.pop();
                //cout<<thePostfix<<endl;
            }
            theone = theone + thePostfix;
            //cout<<"this is the one "<<theone<<endl;
            return theone;

        }
        float PostfixCalculator(std::string exp){
            signed int size = exp.length();

            for(int i =0; i<size;i++)
            {
                if(exp.at(i) == '('){
                    int j=1;
                    while(exp.at(i+j) != ')'){
                        count.push(exp.at(i+j));
                        // cout<<count.top()<<endl;

                        j++;
                    }
                    i = i+j-1;

                }
                else if(exp.at(i) == ')'){
                    float num = 0;
                    int the_power=0;
                    while(!count.empty()){
                        num = num + ((float)(count.pop()-'0')) * power(10,the_power);
                        the_power++;
                    }
                    calc_float.push(num);
                }
                else if(exp.at(i) == '+'){
                    //cout<<"caole1\n";
                    float ans = calc_float.pop() + calc_float.pop();
                    //cout<<ans<<endl;
                    calc_float.push(ans);
                }
                else if(exp.at(i) == '-'){
                    //float answer = -(calc_float.pop() - calc_float.pop());

                    float v1 = calc_float.pop();
                    float v2 = calc_float.pop();
                    float answer = v2-v1;
                    //cout<<ans<<endl;
                    calc_float.push(answer);
                }
                else if(exp.at(i) == '*'){
                    //cout<<"caole3\n";
                    float ans = calc_float.pop() * calc_float.pop();
                    //cout<<ans<<endl;
                    calc_float.push(ans);
                }

                else if(exp.at(i) == '/'){
                    //float answer = (1/(calc_float.pop()/calc_float.pop()));

                    float v1 = calc_float.pop();
                    float v2 = calc_float.pop();

                    float answer = v2/v1;
                    //cout<<ans<<endl;
                    calc_float.push(answer);
                }
            }

           return calc_float.pop();

        }
        int power(int x, int y) {
        int i,power=1;
        if(y == 0)
        return 1;
        for(i=1;i<=y;i++)
        power=power*x;
        return power;
        }

};
