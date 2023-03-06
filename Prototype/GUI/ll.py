class Node :
    def __init__(self, dataValue=None, loopNode=False, loopToNode=None, loopCount=None):
        #self.nodeID
        self.dataValue = dataValue
        self.loopNode = loopNode
        self.loopToNode = loopToNode
        self.loopCount = loopCount
        self.nextNode = None

    def loopVar(self, loopBackNode):
        self.nextNode = loopBackNode

    def getValue(self) :
            return self.dataValue

    def getLoopNode(self) :
        return self.loopNode
    
    def getLoopCount(self) :
        return self.loopCount


class LinkedList :
    def __init__(self):
        self.headNode = None
        self.tailNode = None
        self.ListSize = 0
    
    def sizeOfList(self) :
        return self.ListSize
    
    def push(self, val, loopNode, loopCount, loopToNode, loopBackToNode) :
        """Push node into linked list:
        Normal nodes are queued in a list if loopNode is false.
        If loopNode is true then the node will be link to the loopBackToNode number node in the linked list."""
        newNode = Node(val, loopNode, loopToNode, loopCount)
        size = self.sizeOfList()
        if size == 0 :
            self.headNode = newNode
        else : 
            tempNode = self.headNode
            newNode.nextNode = None
            while tempNode.nextNode is not None :
                tempNode = tempNode.nextNode
            tempNode.nextNode = newNode
        self.ListSize += 1
                
    def deleteNode(self) :
        previousNode = None
        nextNode = None
        currentNode = None

    def AtBeginning(self, newData) :
        # place node at beginning of list
        newNode = Node(newData)
        newNode.nextNode = self.headNode
        self.headNode = newNode

    def runList(self) :
        print("Running List Operation:")
        printVal = self.headNode
        while printVal is not None :
            if printVal.loopNode == True :
                if printVal.loopCount > 0 : 
                    # if there is 1 or more loops left in the list
                    print(printVal.dataValue)
                    count = 1
                    tempNode = self.headNode
                    while printVal.loopToNode != count :
                        # while the node is not the loop back to node
                        tempNode = tempNode.nextNode
                        ++count
                    --printVal.loopCount
                else :
                    # if there are 0 loops left for the node, delete the node and reconnect the list
                    printVal = printVal.nextNode
            else :
                # regular node of the list
                print(printVal.dataValue)
                printVal = printVal.nextNode
                    
    def printList(self) :
        # print the linked list / run the operation
        print("Printing List:")
        printVal = self.headNode
        while printVal is not None :
            #if printVal.getLoopNode :
                #if --printVal.loopCount > 0 :

            print(printVal.dataValue)
            printVal = printVal.nextNode


list = LinkedList()

#list.headNode = Node(2, False, None)
#list.ListSize = 1

list.push(10, False, None, None, None)
list.push(3, False, None, None, None)
list.push(7, True, 2, 1, 3)
list.push(6, False, None, None, None)

list.printList()
list.runList()