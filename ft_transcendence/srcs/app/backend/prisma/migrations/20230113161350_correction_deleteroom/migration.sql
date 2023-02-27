-- DropForeignKey
ALTER TABLE "Message" DROP CONSTRAINT "Message_roomID_fkey";

-- AddForeignKey
ALTER TABLE "Message" ADD CONSTRAINT "Message_roomID_fkey" FOREIGN KEY ("roomID") REFERENCES "Room"("id") ON DELETE CASCADE ON UPDATE CASCADE;
