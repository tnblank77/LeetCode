// Woke up during a bad severe thundestorm I can't sleep through curious if Kotlin would have been a better choice for me
// Timed myself and took ~30 minutes to do this, and less lines of code

class Solution {
    // Data class for the message type
    private data class MessageInfo(
        val timestamp : Int,
        val id: Int,
        val payload_size: Int,
        val payload: List<Int>
    ) 

    // Message buffer
    private val messageBuffer = mutableListOf<MessageInfo>()

    // Main test function
    fun main(): Int {
        // Testing class
        println("Testing message information initialization")
        val testMessageInfo = MessageInfo(1234, 56, 10, listOf(1,2,3,4,5,6,7,8,9,10))
        println(testMessageInfo.toString())

        // Testing parsing a message
        println("\nTesting parsing a message")
        val testParseMessage = parseMessage("0190280A0102030405060708090A")
        println(testParseMessage.toString())

        //Test adding to buffer
        println("\nTest adding to a buffer")
        
        println("DEBUG adding 1")
        messageAdd("23e8990b0b38e56fa24e55c1c628b35012")
        messageBuffer.forEach { msg -> println( msg.toString()) }

        println("DEBUG adding 4 more")
        messageAdd("8894900c0c3237dc5e2d79f4217f976e5393")
        messageAdd("bd9ae50d0d235efa639b329b53f4d40e4b5149")
        messageAdd("3061450e0e5a4ba7b7ac622a92e570e4f58769a1")
        messageAdd("03ba0b0f0ff1407457d97ffe7bb59e79f50a4ea6e5")
        messageBuffer.forEach { msg -> println( msg.toString()) }

        println("DEBUG finding oldest")
        println(messageFindOldest()?.toString())

        println("DEBUG adding 1 more")
        messageAdd("c28a7e0a0a3fa00c17993665101d50fe")
        messageBuffer.forEach { msg -> println( msg.toString()) }

        println("DEBUG adding 1 more")
        messageAdd("0dc9e50a0abd737ca2fe5ba23a2785f2")
        messageBuffer.forEach { msg -> println( msg.toString()) }

        println("DEBUG adding 1 more")
        messageAdd("3894d40a0a947b5286fb11452260118f")
        messageBuffer.forEach { msg -> println( msg.toString()) }

        println("DEBUG adding 1 more")
        messageAdd("f987970a0af69cf2fd6ce5e6406ffa35")
        messageBuffer.forEach { msg -> println( msg.toString()) }

        return 0
    }

    // Function to add a message to the buffer
    private fun messageAdd(hexString: String) {
        // Parse message
        val parsedMessage = parseMessage(hexString)

        // If buffer is full, find oldest
        val oldest = if( messageBuffer.size == 5 ) {
            messageFindOldest()
        } else {
            null
        }

        // If the oldest exist and is older than the parse message, remove it
        oldest?.let {
            if( it.timestamp < parsedMessage.timestamp ) {
                println("DEBUG: new message (${parsedMessage.timestamp}) replacing oldest message (${it.timestamp})")
                messageBuffer.remove(it)
            } else {
                println("DEBUG: new message (${parsedMessage.timestamp}) older than oldest message (${it.timestamp})")
                return
            }
        }

        // Add new message to buffer
        messageBuffer.add(parsedMessage)
    }

    // Function to retrieve the oldest message
    private fun messageFindOldest() : MessageInfo? {
        return messageBuffer.minByOrNull { it.timestamp }
    }

    // Function to parse an input message as hex string into the data type
    private fun parseMessage(hexString: String) : MessageInfo {
        val payload_size = (hexString.substring(6,8).hexToInt())

        val payload = mutableListOf<Int>()
        for(i in 0 .. (payload_size - 1)) {
            val startIdx = (8 + (i * 2))
            payload.add(
                 hexString.substring(startIdx, startIdx+2).hexToInt()
            )
        }

        return MessageInfo(
            timestamp = (hexString.substring(0,4).hexToInt()),
            id = (hexString.substring(4,6).hexToInt()),
            payload_size = payload_size,
            payload = payload.toList()
        )
    }
}