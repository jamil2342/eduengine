using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace ManagedDLL
{
    // Interface declaration.

}
namespace firstMoneyClient
{
    //public interface ICalculator
    //{
    //    int Add(int Number1, int Number2);
    //};

    //// Interface implementation.
    //public class ManagedClass : ICalculator
    //{
    //    public int Add(int Number1, int Number2)
    //    {
    //        return Number1 + Number2;
    //    }
    //}
    //[Guid("5193e42b-cbd7-42ab-83d1-e1598c3eacff")]
    public interface IInterface
    {
        void Connect();

        void Disconnect();
    }

    //[Guid("5193e42b-cbd7-42ab-83d1-e1598c3eacff")]
    public class ClassYouWantToUse:IInterface
    {
        private bool connected;

        public ClassYouWantToUse()
        {

        }
        public void Connect()
        {
            //return 15;
            //add code here
        }

        public void Disconnect()
        {
            //add code here
        }
    }
    //public class Class1
    //{

    //    public void callWebservice()
    //    {

    //    }
    //}
}
