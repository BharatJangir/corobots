/* Auto-generated by genmsg_cpp for file /home/spyder/corobot_ws/src/face_recognition/msg/FaceRecognitionFeedback.msg */
#ifndef FACE_RECOGNITION_MESSAGE_FACERECOGNITIONFEEDBACK_H
#define FACE_RECOGNITION_MESSAGE_FACERECOGNITIONFEEDBACK_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace face_recognition
{
template <class ContainerAllocator>
struct FaceRecognitionFeedback_ {
  typedef FaceRecognitionFeedback_<ContainerAllocator> Type;

  FaceRecognitionFeedback_()
  : order_id(0)
  , names()
  , confidence()
  {
  }

  FaceRecognitionFeedback_(const ContainerAllocator& _alloc)
  : order_id(0)
  , names(_alloc)
  , confidence(_alloc)
  {
  }

  typedef uint8_t _order_id_type;
  uint8_t order_id;

  typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _names_type;
  std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  names;

  typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _confidence_type;
  std::vector<float, typename ContainerAllocator::template rebind<float>::other >  confidence;


  typedef boost::shared_ptr< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct FaceRecognitionFeedback
typedef  ::face_recognition::FaceRecognitionFeedback_<std::allocator<void> > FaceRecognitionFeedback;

typedef boost::shared_ptr< ::face_recognition::FaceRecognitionFeedback> FaceRecognitionFeedbackPtr;
typedef boost::shared_ptr< ::face_recognition::FaceRecognitionFeedback const> FaceRecognitionFeedbackConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace face_recognition

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1354b7478703dcb5d9e033b8bdfafb3b";
  }

  static const char* value(const  ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x1354b7478703dcb5ULL;
  static const uint64_t static_value2 = 0xd9e033b8bdfafb3bULL;
};

template<class ContainerAllocator>
struct DataType< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "face_recognition/FaceRecognitionFeedback";
  }

  static const char* value(const  ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
uint8   order_id\n\
string[]  names\n\
float32[] confidence\n\
\n\
\n\
\n\
\n\
\n\
\n\
################# order_id\n\
#order_id = 0: recognize_once\n\
#order_id = 1: recognize_continuous\n\
#order_id = 2  add_face_images\n\
#order_id = 3  (re)train\n\
#order_id = 4  exit\n\
\n\
################ order_argument\n\
# for the add_face_images goal, the order_argument specifies the name of the person for which training images are acquired from the camera.\n\
\n\
################ name and confidence in feedback and result\n\
# for Order_id = 0 or 1, name and confidence are the name and confidence of the recognized person in the video stream.\n\
\n\
\n\
";
  }

  static const char* value(const  ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.order_id);
    stream.next(m.names);
    stream.next(m.confidence);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct FaceRecognitionFeedback_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::face_recognition::FaceRecognitionFeedback_<ContainerAllocator> & v) 
  {
    s << indent << "order_id: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.order_id);
    s << indent << "names[]" << std::endl;
    for (size_t i = 0; i < v.names.size(); ++i)
    {
      s << indent << "  names[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.names[i]);
    }
    s << indent << "confidence[]" << std::endl;
    for (size_t i = 0; i < v.confidence.size(); ++i)
    {
      s << indent << "  confidence[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.confidence[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // FACE_RECOGNITION_MESSAGE_FACERECOGNITIONFEEDBACK_H

