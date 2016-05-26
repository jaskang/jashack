
PLAYER_STATE_GOLD=1;    --当前黄金
PLAYER_STATE_E_LUMBER=2;    --当前木材

UNIT_STATE_LIFE=0;      --生命值
UNIT_STATE_MAX_LIFE=1;  --最大生命值
UNIT_STATE_MANA=2;      --魔法值
UNIT_STATE_MAX_MANA=3;  --最大魔法值


--常量-玩家颜色 [系统接口]
local PlayerColor={"|c00ff0000","|c000000ff","|c0018e7bd","|c00520084","|c00ffff00","|c00ff8a08","|c0018be00","|c00e759ad","|c00949694","|c007bbef7","|c00086142","|c004a2800","|c00909090"};
--常量-信号颜色 [系统接口]
local PingColor = {yellow=1,blue=2,green=3,red=4}
--常量-单位控制者 [系统接口]
local PlayerController = {"玩家","电脑"};
--产量-坐标 [系统接口]
local Loc={shuguo={X=-6832.00,Y=-7694.00},weiguo={X=6968.00,Y=5329.00}}

LocalPlayer = {id=nil,handle=nil,team=nil}

LocalHero = nil;
--变量-游戏状态 [系统接口]
local isINGame = false;
--变量-本地队伍 [系统接口]
local LocalGuo=nil;
--常量-真三国无双-技能表 [系统接口]
local CommandTable = {
["司马懿"]={[852224]="星落"},
["诸葛亮"]={[852127]="卧龙光线",[852592]="级冻凝结"},
["张飞"]={[852127]="动地跺",[852100]="狂战士",[852086]="万夫莫敌"},
["典韦"]={[852127]="动地跺"},
["关羽"]={[852127]="五月雨斩"}
};

--常量-真三国无双-物品表 [系统接口]
local ItemTypeTable={
["翔靴"]=0x64657363,
["玄武斧"]=0x49303243,
["羊杖"]=0x7373616E,
["风暴之杖"]=0x736E6567,
["风行"]=0x49303150
};




-- ////////////////////////////////////////////////////////////////////////////////////


function UseItem(itemtypeid)
    if LocalHero ~=nil then
        for i=0,5 do
            local hitem = UnitItemInSlot(LocalHero,i);
            if GetItemTypeId(hItem) == itemtypeid then
                if IsItemUseable(hitem,i) then
                    SendItem(LocalHero,852008+i,hitem);
                    return true;
                else
                    return false;
                end
            end
        end
    end
    return false
end

function UseItemLoc(itemtypeid,x,y)
    if LocalHero >0 then
        for i=0,5 do
            local hitem = UnitItemInSlot(LocalHero,i);
            ScreenText('hitem'..i..':'..hitem,10.0)
            if GetItemTypeId(hItem) == itemtypeid then
                ScreenText('找到物品',10.0)
                if IsItemUseable(hitem,i) then
                    ScreenText('使用物品',10.0)
                    SendItemLoc(LocalHero,852008+i,hitem,x,y);
                    return true;
                else
                    ScreenText('物品cd中',10.0)
                    return false;
                end
            end
        end
    end
    return false
end


--取单位id [系统函数]
function GetUnitId(hunit)
    local typeid=GetUnitTypeId(hunit);
    if typeid==0 then
        return nil;
    end
    local hex=string.format('%X',typeid);
    local s1= tonumber('0x'..string.sub(hex,1,-7));
    local s2=tonumber('0x'..string.sub(hex,3,-5));
    local s3=tonumber('0x'..string.sub(hex,5,-3));
    local s4=tonumber('0x'..string.sub(hex,7,-1));
    return string.format("%c%c%c%c",s1,s2,s3,s4);
end
--取物品id [系统函数]
function GetItemId(hItem)
    local typeid=GetItemTypeId(hItem);
    if typeid==0 then
        return nil;
    end
    local hex=string.format('%X',typeid);
    local s1= tonumber('0x'..string.sub(hex,1,-7));
    local s2=tonumber('0x'..string.sub(hex,3,-5));
    local s3=tonumber('0x'..string.sub(hex,5,-3));
    local s4=tonumber('0x'..string.sub(hex,7,-1));
    return string.format("%c%c%c%c",s1,s2,s3,s4);
end

function copyTable(tbobj)
    local tab = {}
    for k, v in pairs(tbobj or {}) do
        if type(v) ~= "table" then
            tab[k] = v
        else
            tab[k] = copyTable(v)
        end
    end
    return tab
end 



-- /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function Init()
    isINGame=false
end


-- #define GS_NOTHING 0    //主页
-- #define GS_LOBBY 1      //大厅
-- #define GS_LOADING 3    //loading
-- #define GS_INGAME 4     //游戏中
-- #define GS_PAUSEDGAME 6 //暂停
--  [系统接口]
function GameStateChange(state)
    if state==4 then
        isINGame=true
    else
        isINGame=false
    end
end

--  [系统接口]
function GameBegin()
    Sleep(3000);
    LocalPlayer.handle=GetLocalPlayer();
    LocalPlayer.id=GetPlayerId(LocalPlayer.handle);
    
    LocalPlayer.team=GetPlayerTeam(LocalPlayer.handle);
    ScreenText('id:'..LocalPlayer.id..'  handle:'..LocalPlayer.handle..'  team:'..LocalPlayer.team)
    if LocalPlayer.id<=5 then
        LocalGuo=Loc.shuguo;
    else
        LocalGuo=Loc.weiguo;
    end


    -- for i=0,12 do
    --     local hPlayer =Player(i);
    --     local controller = GetPlayerController(hPlayer);
    --     if controller==0 then
    --         ScreenText('index:'..i..'hplayer:'..hPlayer..'  '..PlayerColor[(i+1)]..GetPlayerName(hPlayer)..'|r'..'  金钱:'..GetPlayerState(hPlayer,1)..'  木材:'..GetPlayerState(hPlayer,2),10);
    --     end
    --     if controller==1 then
    --         ScreenText('index:'..i..'hplayer:'..hPlayer..'  '..PlayerColor[(i+1)]..GetPlayerName(hPlayer)..'|r'..'  金钱:'..GetPlayerState(hPlayer,1)..'  木材:'..GetPlayerState(hPlayer,2),10);
    --     end
    -- end
end
--  [系统接口]
function GameOver() 
    LocalPlayer.id=nil;
    LocalPlayer.handle=nil;
    LocalPlayer.team=nil;
    LocalHero=nil;
end


--hook单位动作 [系统接口] 4F303033
function hookCommand(hunit,commandId,posx,posy,targethunit)
    ScreenText('LocalHero:'..GetUnitName(LocalHero),3.0);
    if commandId>=852008 and commandId<=852013 then
        local slot=commandId-852008;
        local hItem=UnitItemInSlot(hunit,slot);
        ScreenText(string.format('%s 使用物品 %s',GetUnitName(hunit),GetItemName(hItem)),3.0);
    else 
        if targethunit==0 then
            ScreenText(GetUnitName(hunit)..' 使用:'..string.format("%X", commandId)..' X:'..posx..' Y:'..posy,10.0);
        else
            ScreenText(string.format('%s[%s] 对 %s[%s] 使用 %X',GetUnitName(hunit),GetUnitId(hunit),GetUnitName(targethunit),GetUnitId(targethunit),commandId),10.0);
        end
        if CommandTable[GetUnitName(hunit)]~=nil then
            ScreenText('找到单位：'..GetUnitName(hunit),10.0)
            if CommandTable[GetUnitName(hunit)][commandId]~=nil then
                ScreenText('找到commandId：'..CommandTable[GetUnitName(hunit)][commandId],10.0)
                if IsUnitEnemy(hunit,LocalPlayer.handle) then
                    ScreenText('敌人',10.0)
                    if CommandTable[GetUnitName(hunit)][commandId]=='动地跺' then
                        -- if UseItem(ItemTypeTable['玄武斧']) then 
                        --     ScreenText('触发玄武',10.0)
                        --     return
                        -- end
                        local hitem = UnitItemInSlot(LocalHero,0);
                        SendItemLoc(LocalHero,852008,hitem,x,y);
                    end
                else
                    ScreenText('自己人',10.0)
                end
            else
                ScreenText('没有：'..commandId,10.0)
            end
        else
            ScreenText('没有：'..GetUnitName(hunit),10.0)
        end
    end
end


-- 资源交易【系统回调】
function hookResource(formPlayid,toPlayerid,good,wood)
    ScreenText(string.format("反挂助手：|cFFFF0000%s|r |cFFDDDDDD给|r |cFFFF0000%s|r |cFFFFFF00%d|r|cFFDDDDDD[金]|r |cFF00FF00%d|r|cFFDDDDDD[木]|r ",GetPlayerName(Player(formPlayid)),GetPlayerName(Player(toPlayerid)),good,wood),10)
    
    if IsPlayerEnemy(Player(formPlayid),LocalPlayer.handle) then
        Chat(string.format("反挂助手提示大家：%s 给 %s %d[金] %d[木] ",GetPlayerName(Player(formPlayid)),GetPlayerName(Player(toPlayerid)),good,wood),true);  
    end
end