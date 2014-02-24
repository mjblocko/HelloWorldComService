using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelloWorldComService;

namespace HelloWorldComClient_CS
{
  class Program
  {
    static void Main(string[] args)
    {
      var comServer = new SimpleObject();

      var str = comServer.HelloWorld();

      Console.WriteLine("Hello World Returned {0}", str);
    }
  }
}
