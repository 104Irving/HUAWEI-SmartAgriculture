import FarmBean from './Farmbean';
export default class UserInfoBean {
  Username: string;//用户名
  UserID: number //用户的ID
  UserIcon: string;//用户头像
  UserFarmList: number[];//用户管理的农田列表的ID


  //相当于是初始化函数
  constructor(UserName:string, UserID:number, UserFarm:number[])
  {
    this.Username = UserName
    this.UserID = UserID
    this.UserFarmList = UserFarm
  }
}
