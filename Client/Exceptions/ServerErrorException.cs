using System;

namespace NetTalk.Exceptions
{
    [Serializable]
    public class ServerErrorException : Exception
    {
        public ServerErrorException()
        {
        }

        public ServerErrorException(string message) : base(message)
        {
        }

        public ServerErrorException(string message, Exception inner) : base(message, inner)
        {
        }

        protected ServerErrorException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context) : base(info, context) { }
    }
}