-- CreateTable
CREATE TABLE "APPUser" (
    "id" SERIAL NOT NULL,
    "login" TEXT NOT NULL,
    "pseudo" TEXT NOT NULL,
    "avatar" TEXT NOT NULL,
    "twoFactorAuthSecret" TEXT NOT NULL DEFAULT '',
    "twoFactorAuthEnabled" BOOLEAN NOT NULL DEFAULT false,
    "elo" INTEGER NOT NULL DEFAULT 1000,
    "nb_played_game" INTEGER NOT NULL DEFAULT 0,
    "nb_victory" INTEGER NOT NULL DEFAULT 0,
    "nb_defeat" INTEGER NOT NULL DEFAULT 0,

    CONSTRAINT "APPUser_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Follows" (
    "followingID" INTEGER NOT NULL,
    "followedID" INTEGER NOT NULL,

    CONSTRAINT "Follows_pkey" PRIMARY KEY ("followingID","followedID")
);

-- CreateTable
CREATE TABLE "Blocks" (
    "blockerID" INTEGER NOT NULL,
    "blockedID" INTEGER NOT NULL,

    CONSTRAINT "Blocks_pkey" PRIMARY KEY ("blockerID","blockedID")
);

-- CreateTable
CREATE TABLE "Room" (
    "id" SERIAL NOT NULL,
    "name" TEXT NOT NULL,
    "haspass" BOOLEAN NOT NULL DEFAULT false,
    "password" TEXT,
    "visible" BOOLEAN NOT NULL DEFAULT false,

    CONSTRAINT "Room_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Authorization" (
    "id" SERIAL NOT NULL,
    "name" TEXT NOT NULL,

    CONSTRAINT "Authorization_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Message" (
    "id" SERIAL NOT NULL,
    "content" TEXT NOT NULL,
    "timestamp" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "roomID" INTEGER NOT NULL,
    "appuserID" INTEGER NOT NULL,

    CONSTRAINT "Message_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Game" (
    "id" SERIAL NOT NULL,
    "ranked" BOOLEAN NOT NULL DEFAULT false,
    "timestamp" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "p1_score" INTEGER NOT NULL,
    "p2_score" INTEGER NOT NULL,

    CONSTRAINT "Game_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "APPUsersPlayGames" (
    "player1ID" INTEGER NOT NULL,
    "player2ID" INTEGER NOT NULL,
    "gameID" INTEGER NOT NULL,

    CONSTRAINT "APPUsersPlayGames_pkey" PRIMARY KEY ("player1ID","player2ID","gameID")
);

-- CreateTable
CREATE TABLE "Status" (
    "id" SERIAL NOT NULL,
    "status" TEXT NOT NULL,

    CONSTRAINT "Status_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Game_Status" (
    "GameID" INTEGER NOT NULL,
    "StatusID" INTEGER NOT NULL,

    CONSTRAINT "Game_Status_pkey" PRIMARY KEY ("GameID","StatusID")
);

-- CreateTable
CREATE TABLE "Access" (
    "appuserID" INTEGER NOT NULL,
    "AuthorizationID" INTEGER NOT NULL,
    "roomID" INTEGER NOT NULL,

    CONSTRAINT "Access_pkey" PRIMARY KEY ("appuserID","AuthorizationID","roomID")
);

-- CreateIndex
CREATE UNIQUE INDEX "APPUser_id_key" ON "APPUser"("id");

-- CreateIndex
CREATE UNIQUE INDEX "APPUser_login_key" ON "APPUser"("login");

-- CreateIndex
CREATE UNIQUE INDEX "Room_id_key" ON "Room"("id");

-- CreateIndex
CREATE UNIQUE INDEX "Authorization_id_key" ON "Authorization"("id");

-- CreateIndex
CREATE UNIQUE INDEX "Message_id_key" ON "Message"("id");

-- CreateIndex
CREATE UNIQUE INDEX "Game_id_key" ON "Game"("id");

-- CreateIndex
CREATE UNIQUE INDEX "APPUsersPlayGames_gameID_key" ON "APPUsersPlayGames"("gameID");

-- CreateIndex
CREATE UNIQUE INDEX "Status_id_key" ON "Status"("id");

-- AddForeignKey
ALTER TABLE "Follows" ADD CONSTRAINT "Follows_followingID_fkey" FOREIGN KEY ("followingID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Follows" ADD CONSTRAINT "Follows_followedID_fkey" FOREIGN KEY ("followedID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Blocks" ADD CONSTRAINT "Blocks_blockerID_fkey" FOREIGN KEY ("blockerID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Blocks" ADD CONSTRAINT "Blocks_blockedID_fkey" FOREIGN KEY ("blockedID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Message" ADD CONSTRAINT "Message_roomID_fkey" FOREIGN KEY ("roomID") REFERENCES "Room"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Message" ADD CONSTRAINT "Message_appuserID_fkey" FOREIGN KEY ("appuserID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "APPUsersPlayGames" ADD CONSTRAINT "APPUsersPlayGames_player1ID_fkey" FOREIGN KEY ("player1ID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "APPUsersPlayGames" ADD CONSTRAINT "APPUsersPlayGames_player2ID_fkey" FOREIGN KEY ("player2ID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "APPUsersPlayGames" ADD CONSTRAINT "APPUsersPlayGames_gameID_fkey" FOREIGN KEY ("gameID") REFERENCES "Game"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Game_Status" ADD CONSTRAINT "Game_Status_GameID_fkey" FOREIGN KEY ("GameID") REFERENCES "Game"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Game_Status" ADD CONSTRAINT "Game_Status_StatusID_fkey" FOREIGN KEY ("StatusID") REFERENCES "Status"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Access" ADD CONSTRAINT "Access_appuserID_fkey" FOREIGN KEY ("appuserID") REFERENCES "APPUser"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Access" ADD CONSTRAINT "Access_AuthorizationID_fkey" FOREIGN KEY ("AuthorizationID") REFERENCES "Authorization"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Access" ADD CONSTRAINT "Access_roomID_fkey" FOREIGN KEY ("roomID") REFERENCES "Room"("id") ON DELETE CASCADE ON UPDATE CASCADE;
