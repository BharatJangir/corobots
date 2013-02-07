#!/usr/bin/env python
import roslib; roslib.load_manifest('corobot_comm')
import rospy
import socket
from geometry_msgs.msg import Point
from corobot_msgs.srv import GetLocation,GetWaypoints
from corobot_msgs.msg import Pose
from queue import PriorityQueue

myPose = None
lastWP = None
mpp = 0.0328 # I should not hard-code this...

def pose_callback(pose):
    global myPose 
    myPose = pose

'''
Can I straight line nav to this wp from current pos?
'''
def navigableTo(wp):
    '''double cx = rPos.getX(), cy = rPos.getY();
    double dx = n.pos.getX()-rPos.getX(), dy = n.pos.getY()-rPos.getY();
    double sdx = Math.signum(dx), sdy = Math.signum(dy);
    double incx, incy;
    if (Math.abs(dx) > Math.abs(dy)) {
        incx = sdx*mpp/2; incy = dy/(dx/incx);
    } else {
        incy = sdy*mpp/2; incx = dx/(dy/incy);
    }
    //System.out.println("Testing going straight to " + n.name + " " + n.pos + " inc (" + 
    //         incx + "," + incy + ") totald (" + dx + "," + dy + ")");
    while (sdx*dx > 0 || sdy*dy > 0) {
        if (mapAt(cx+dx,cy+dy) == 0) {
        return false;
        }
        dx -= incx; dy -= incy;
    }
    return true;
    }'''
    cx = myPose.x
    cy = myPose.y
    dx = wp.x - cx
    dy = wp.y - cy
    sdx = math.copysign(1,dx)
    sdy = math.copysign(1,dy)
    if(math.fabs(dx) > math.fabs(dy)):
        incx = sdx*mpp/2
        incy = dy/(dx/incx)
    else:
        incy = sdy*mpp/2
        incx = dx/(dy/incy)
    mapAt = rospy.ServiceProxy('get_pixel_occupancy',GetPixelOccupancy,persistent=True)
    while(sdx*dx > 0 || sdy*dy > 0):
        occ = mapAt(cx+dx,cy+dy).occupancy
    mapAt.close()


'''
Find nearest Waypoint to the current value of myPose
'''
def findNearestNavigable(wps):
    closest = None
    for wp in wps:
        if closest == None and navigableTo(wp):
            closest = (math.fabs((wp.y - myPose.y)/(wp.x - myPose.x)),wp)
            continue
        dist = math.fabs((wp.y - myPose.y)/(wp.x - myPose.x))
        if dist < closest[0] and navigableTo(wp):
            closest = (dist,wp)
    return closest[1]

def aStar(dest,wps):
    me = findNearestNavigable(wps)
    #Build path from dest back to me.
    return [dest]

def clientComm(socket,addr):
    rospy.init_node('corobot_client_comm')
    clIn = socket.makefile('r')
    clOut = socket.makefile('w')
    #Publisher to obstacle_avoidance
    pointPub = rospy.Publisher('waypoints',Point)
    rospy.Subscriber('pose',Pose,pose_callback)
    
    while True:
        cmd = client.readline()
        if len(cmd) == 0:
            clIn.close()
            clOut.close()
            break
        rospy.loginfo("Command recieved from client %n: %s", addr, cmd)
        cmd = cmd.split(' ')
        if cmd[0] == 'GETPOS':
            if myPose is None:
                clOut.write("POS {} {} {}\n".format(str(0),str(0),str(0)))
                clOut.flush()
            else:
                clOut.write("POS {} {} {}\n".format(str(myPose.x),str(myPose.y),str(myPose.theta)))
                clOut.flush()
        elif cmd[0] == 'GOTOXY':
            #Add dest point!
            pointPub.publish(x=float(cmd[1]),y=float(cmd[2]))
        elif cmd[0] == 'GOTOLOC':
            #Goto location, no navigation
            rospy.wait_for_service('get_location')
            try:
                getLoc = rospy.ServiceProxy('get_location',GetLocation)
                resp = getLoc(cmd[1])
                pointPub.publish(x=resp.wp.x,y=resp.wp.y)
            except rospy.ServiceException as e:
                print("Service call failed: {}".format(e))
        elif cmd[0] == 'NAVTOLOC':
            #Navigate to location
            rospy.wait_for_service('get_waypoints')
            rospy.wait_for_service('get_location')
            try:
                getLoc = rospy.ServiceProxy('get_location',GetLocation)
                getWps = rospy.ServiceProxy('get_waypoints',GetWaypoints)
                #Gets waypoints, no neighbor data...maybe I should change that ~Karl
                wps = getWps()
                start = getLoc(cmd[1])
                path = aStar(start,wps)
                for node in path:
                    pointPub.publish(x=node.x,y=node.y)
            except rospy.ServiceException as e:
                print("Service call failed: {}".format(e))
        elif cmd[0] == 'QUERY_ARRIVE':
            print("Query_Arrive")
            #How to figure this out?!
            


def main():
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversocket.bind( (socket.getHostname(),15001) )
    serversocket.listen( 1 )

    while True:
        (client, clAddr) = serversocket.accept()
        #On connection accept, go into ROS node method
        clientComm(client,clAddr)

if __name__ == '__main__':
    main()