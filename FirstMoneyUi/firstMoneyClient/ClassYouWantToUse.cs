using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using   System.Runtime.InteropServices;


namespace firstMoneyClient
{
    [Guid("5193e42b-cbd7-42ab-83d1-e1598c3eacff")]
    public interface IInterface
    {
        void Connect();

        void Disconnect();
    }
    [Guid("5193e42b-cbd7-42ab-83d1-e1598c3eacff")]
    public class ClassYouWantToUse: IInterface
     {
         private bool connected;

         public void Connect()
         {
             //add code here
         }

         public void Disconnect()
         {
             //add code here
         }
     }
}
